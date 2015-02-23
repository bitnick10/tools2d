package main

import (
	"fmt"
	"image"
	"image/png"
	"os"
	"path/filepath"
)

func get_filenames(folderName, extension string) []string {
	dirname := "." + string(filepath.Separator) + folderName + string(filepath.Separator)
	d, err := os.Open(dirname)
	check(err)
	defer d.Close()

	files, err := d.Readdir(-1)
	check(err)

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
func get_images(folderName string) [][]image.Image {
	filenames := get_filenames(folderName+"/d0", ".png")
	images := make([][]image.Image, 5)
	for i := 0; i < 5; i++ {
		images[i] = make([]image.Image, len(filenames))
	}
	for y := range images {
		for x := range images[y] {
			filename := fmt.Sprintf("%s/d%d/ani_%d.png", folderName, y, x+1)
			// is file exists
			if _, err := os.Stat(filename); os.IsNotExist(err) {
				fmt.Println("Can not find file", filename, "in this directory")
				os.Exit(250)
			}
			imageReader, err := os.Open(filename)
			check(err)
			defer imageReader.Close()
			images[y][x], err = png.Decode(imageReader)
			check(err)
		}
	}
	return images
}

func main() {
	file, err := os.Open("./")
	check(err)
	defer file.Close()
	fileInfo, err := file.Readdir(0)
	check(err)
	for _, fi := range fileInfo {
		if fi.IsDir() {
			fmt.Println("merge", fi.Name())
			merge(fi.Name())
		}
	}
	//merge("standing")
	//fmt.Println(ss)
	return

	var a string
	fmt.Scanln(&a)
}
func merge(folderName string) {
	images := get_images(folderName)

	out, err := os.Create(fmt.Sprintf("./%s.png", folderName))
	check(err)
	defer out.Close()
	//fmt.Println(len(images))
	//fmt.Println(len(images[0]))
	//rect := image.Rect(0, 0, images[0][0].Bounds().Dx()*len(images), images[0][0].Bounds().Dy())
	rect := image.Rect(0, 0, images[0][0].Bounds().Dx()*len(images[0]), images[0][0].Bounds().Dy()*len(images))
	newImage := image.NewRGBA(rect)

	for y := range images {
		for x := range images[y] {
			img := images[y][x]
			for py := 0; py < img.Bounds().Dy(); py++ {
				for px := 0; px < img.Bounds().Dx(); px++ {
					newImage.Set(px+img.Bounds().Dx()*x, py+img.Bounds().Dy()*y, img.At(px, py))
				}
			}
			fmt.Println(fmt.Sprintf("d%d/ani_%d.png has been merged.", y, x+1))
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
