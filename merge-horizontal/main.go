package main

import (
	"fmt"
	"image"
	"image/png"
	"os"
	"path/filepath"
)

func get_filenames(extension string) []string {
	dirname := "." + string(filepath.Separator)
	d, err := os.Open(dirname)
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
	defer d.Close()

	files, err := d.Readdir(-1)
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}

	s := make([]string, 0)

	for _, file := range files {
		if file.Mode().IsRegular() {
			if filepath.Ext(file.Name()) == extension {
				s = append(s, file.Name())
			}
		}
	}
	return s
}
func main() {
	filenames := get_filenames(".png")

	fmt.Printf("There are %d png files to be merge.\n", len(filenames))
	images := make([]image.Image, len(filenames))
	for i, _ := range filenames {
		n := i + 1
		imageReader, err := os.Open(fmt.Sprintf("./ani_%d.png", n))
		check(err)
		defer imageReader.Close()
		images[i], err = png.Decode(imageReader)
	}

	out, err := os.Create("./output.png")
	check(err)
	defer out.Close()
	rect := image.Rect(0, 0, images[0].Bounds().Dx()*len(images), images[0].Bounds().Dy())
	newImage := image.NewRGBA(rect)

	for i, img := range images {
		for y := 0; y < img.Bounds().Dy(); y++ {
			for x := 0; x < img.Bounds().Dx(); x++ {
				newImage.Set(x+img.Bounds().Dx()*i, y, img.At(x, y))
			}
		}
	}

	err = png.Encode(out, newImage)
	check(err)
}
func check(err error) {
	if err != nil {
		fmt.Println(err)
	}
}
