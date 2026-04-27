package main

import (
	"bufio"
	"encoding/json"
	"fmt"
	"image/color"
	"log"
	"os"
	"sync"
	"time"

	"github.com/hajimehoshi/ebiten/v2"
)

const cellSize = 40

type Game struct {
	width  int
	height int
	field  [][]int

	robotX      int
	robotY      int
	robotBroken bool
	exitFound   bool

	drones      [][]Point
	dronesCount int

	explored [][]int

	message      string
	commandQueue chan Command

	mu sync.Mutex
}

type Point struct {
	X int `json:"x"`
	Y int `json:"y"`
}

type Command struct {
	Command string `json:"command"`

	Width      int     `json:"width"`
	Height     int     `json:"height"`
	Field      [][]int `json:"field"`
	RobotX     int     `json:"robot_x"`
	RobotY     int     `json:"robot_y"`
	DroneCount int     `json:"drone_count"`

	X         int    `json:"x"`
	Y         int    `json:"y"`
	Direction string `json:"direction"`

	Status  string `json:"status"`
	Message string `json:"message"`

	Count           int       `json:"count"`
	DronesRemaining int       `json:"drones_remaining"`
	Paths           [][]Point `json:"paths"`

	Name string `json:"name"`

	RobotBroken bool `json:"robot_broken"`
	FinalX      int  `json:"final_x"`
	FinalY      int  `json:"final_y"`
}

var (
	game = &Game{
		drones:       make([][]Point, 0),
		commandQueue: make(chan Command, 100000),
	}

	// Цвета
	undefColor    = color.RGBA{60, 60, 60, 255}    // неразведано - темно-серый
	emptyExplored = color.RGBA{144, 238, 144, 255} // пусто - салатовый
	exitExplored  = color.RGBA{0, 100, 0, 255}     // выход - темно-зеленый
	wallExplored  = color.RGBA{255, 50, 50, 255}   // стена - красный
	robotColor    = color.RGBA{50, 50, 255, 255}   // робот - синий
	brokenColor   = color.RGBA{255, 0, 0, 255}     // сломан - красный
	droneColor    = color.RGBA{255, 200, 0, 255}   // дрон - желтый
	bgColor       = color.RGBA{20, 20, 20, 255}    // фон
)

func (g *Game) Update() error {
	select {
	case cmd := <-g.commandQueue:
		handleCommand(cmd)
	default:
	}
	return nil
}
func (g *Game) Draw(screen *ebiten.Image) {
	g.mu.Lock()
	defer g.mu.Unlock()

	screen.Fill(bgColor)

	sw, sh := screen.Bounds().Dx(), screen.Bounds().Dy()
	scaleX := float64(sw-40) / float64(g.width*cellSize)
	scaleY := float64(sh-40) / float64(g.height*cellSize)
	scale := scaleX
	if scaleY < scaleX {
		scale = scaleY
	}
	if scale > 1.0 {
		scale = 1.0
	}

	offsetX := (float64(sw) - float64(g.width*cellSize)*scale) / 2
	offsetY := (float64(sh) - float64(g.height*cellSize)*scale) / 2

	for y := 0; y < g.height; y++ {
		for x := 0; x < g.width; x++ {
			var col color.Color

			switch g.field[y][x] {
			case 0:
				col = emptyExplored // EMPTY - салатовый
			case 1:
				col = wallExplored // WALL - красный
			case 2:
				col = exitExplored // EXIT - темно-зеленый
			default:
				col = emptyExplored
			}

			drawCellScaled(screen, x, y, col, scale, offsetX, offsetY)
		}
	}

	for _, path := range g.drones {
		for _, p := range path {
			drawDroneScaled(screen, p.X, p.Y, droneColor, scale, offsetX, offsetY)
		}
	}

	robotCol := robotColor
	if g.robotBroken {
		robotCol = brokenColor
	} else if g.exitFound {
		robotCol = color.RGBA{50, 255, 50, 255}
	}
	drawRobotScaled(screen, g.robotX, g.robotY, robotCol, scale, offsetX, offsetY)
}

func (g *Game) Layout(outsideWidth, outsideHeight int) (int, int) {
	return outsideWidth, outsideHeight
}

func drawCellScaled(screen *ebiten.Image, x, y int, col color.Color, scale, offsetX, offsetY float64) {
	size := cellSize - 2
	w := float64(size) * scale
	h := float64(size) * scale
	if w < 1 {
		w = 1
	}
	if h < 1 {
		h = 1
	}
	rect := ebiten.NewImage(int(w), int(h))
	rect.Fill(col)

	op := &ebiten.DrawImageOptions{}
	op.GeoM.Scale(scale, scale)
	op.GeoM.Translate(
		offsetX+float64(x*cellSize+1)*scale,
		offsetY+float64(y*cellSize+1)*scale,
	)
	screen.DrawImage(rect, op)
}

func drawDroneScaled(screen *ebiten.Image, x, y int, col color.Color, scale, offsetX, offsetY float64) {
	size := cellSize - 10
	w := float64(size) * scale
	h := float64(size) * scale
	if w < 1 {
		w = 1
	}
	if h < 1 {
		h = 1
	}
	rect := ebiten.NewImage(int(w), int(h))
	rect.Fill(col)

	op := &ebiten.DrawImageOptions{}
	op.GeoM.Scale(scale, scale)
	op.GeoM.Translate(
		offsetX+float64(x*cellSize+5)*scale,
		offsetY+float64(y*cellSize+5)*scale,
	)
	screen.DrawImage(rect, op)
}

func drawRobotScaled(screen *ebiten.Image, x, y int, col color.Color, scale, offsetX, offsetY float64) {
	size := cellSize - 4
	w := float64(size) * scale
	h := float64(size) * scale
	if w < 1 {
		w = 1
	}
	if h < 1 {
		h = 1
	}
	rect := ebiten.NewImage(int(w), int(h))
	rect.Fill(col)

	op := &ebiten.DrawImageOptions{}
	op.GeoM.Scale(scale, scale)
	op.GeoM.Translate(
		offsetX+float64(x*cellSize+2)*scale,
		offsetY+float64(y*cellSize+2)*scale,
	)
	screen.DrawImage(rect, op)

	// Белая рамка
	borderH := float64(2) * scale
	if borderH < 1 {
		borderH = 1
	}
	border := ebiten.NewImage(int(w), int(borderH))
	border.Fill(color.White)
	op2 := &ebiten.DrawImageOptions{}
	op2.GeoM.Scale(scale, scale)
	op2.GeoM.Translate(
		offsetX+float64(x*cellSize+2)*scale,
		offsetY+float64(y*cellSize+2)*scale,
	)
	screen.DrawImage(border, op2)
	op2.GeoM.Translate(0, h-float64(2)*scale)
	screen.DrawImage(border, op2)
}

func handleCommand(cmd Command) {
	game.mu.Lock()
	defer game.mu.Unlock()

	switch cmd.Command {

	case "init":
		game.width = cmd.Width
		game.height = cmd.Height
		game.field = cmd.Field
		game.robotX = cmd.RobotX
		game.robotY = cmd.RobotY
		game.dronesCount = cmd.DroneCount

		game.explored = make([][]int, game.height)
		for i := range game.explored {
			game.explored[i] = make([]int, game.width)
			for j := range game.explored[i] {
				game.explored[i][j] = -1
			}
		}

		fmt.Printf("Map loaded: %dx%d, Robot: (%d,%d), Drones: %d\n",
			cmd.Width, cmd.Height, cmd.RobotX, cmd.RobotY, cmd.DroneCount)

	case "start":
		fmt.Println("=== PROGRAM STARTED ===")

	case "robot_move":
		oldX, oldY := game.robotX, game.robotY
		game.robotX = cmd.X
		game.robotY = cmd.Y

		if game.explored[cmd.Y][cmd.X] == -1 {
			game.explored[cmd.Y][cmd.X] = game.field[cmd.Y][cmd.X]
		}

		fmt.Printf("Robot: (%d,%d) -> (%d,%d)\n", oldX, oldY, cmd.X, cmd.Y)

	case "robot_status":
		if cmd.Status == "broken" {
			game.robotBroken = true
			fmt.Println("--ROBOT BROKEN:", cmd.Message)
		} else if cmd.Status == "exit_found" {
			game.exitFound = true
			fmt.Println("--EXIT FOUND!")
		}
		game.message = cmd.Message

	case "drones_launched":
		game.dronesCount = cmd.DronesRemaining
		game.drones = cmd.Paths

		for _, path := range cmd.Paths {
			for _, p := range path {
				if p.X >= 0 && p.X < game.width && p.Y >= 0 && p.Y < game.height {
					game.explored[p.Y][p.X] = game.field[p.Y][p.X]
				}
			}
		}

		fmt.Printf("--Drones: %d launched, %d remaining\n", cmd.Count, cmd.DronesRemaining)

	case "drone_count_queried":
		game.dronesCount = cmd.Count

	case "function_call":
		fmt.Printf("--Calling: %s\n", cmd.Name)

	case "finished":
		game.robotX = cmd.FinalX
		game.robotY = cmd.FinalY
		game.robotBroken = cmd.RobotBroken
		fmt.Printf("=== FINISHED === Robot at (%d,%d)\n", cmd.FinalX, cmd.FinalY)
		if cmd.RobotBroken {
			fmt.Println("--Robot is BROKEN")
		}

	case "exit":
		time.Sleep(500 * time.Millisecond)
		os.Exit(0)
	}
}

func readInput() {
	scanner := bufio.NewScanner(os.Stdin)
	buf := make([]byte, 0, 1024*1024)
	scanner.Buffer(buf, 10*1024*1024)

	for scanner.Scan() {
		line := scanner.Text()
		if line == "" {
			continue
		}

		var cmd Command
		if err := json.Unmarshal([]byte(line), &cmd); err != nil {
			fmt.Fprintf(os.Stderr, "JSON error: %v\n", err)
			continue
		}

		game.commandQueue <- cmd

		// Задержка 500 мс между командами (кроме init)
		if cmd.Command != "init" && cmd.Command != "exit" {
			time.Sleep(300 * time.Millisecond)
		}
	}
}

func main() {
	go readInput()

	ebiten.SetWindowSize(800, 800)
	ebiten.SetWindowTitle("Robot Visualizer")
	ebiten.SetWindowResizingMode(ebiten.WindowResizingModeEnabled)
	ebiten.SetTPS(60)

	fmt.Println("Visualizer started. Waiting for commands...")

	if err := ebiten.RunGame(game); err != nil {
		log.Fatal(err)
	}
}
