# ut_bmp_converter
This repo provides a few commands for bitmap conversion: gray scale conversion, thermography, and posterization.
The repo is created as part of Image Processing lecture in the University of Tokyo.

## Usage
```
$ git clone https://github.com/sykwer/ut_bmp_converter.git
$ cd ut_bmp_converter
$ make
```

Make command creates theree executable: `gray`, `thermo`, `posterize`.
You can use these commands as below.
```
command <bmp_file_name.bmp> <output_file_name.bmp>
```
which creates new bmp file in the same directory.

## Screenshots
#### Original
<img width="400" alt="2018-05-06 23 08 05" src="https://user-images.githubusercontent.com/18254663/39674150-8cf50eca-5182-11e8-9c3d-47c5dd98199c.png">

#### Grayscale
<img width="400" alt="2018-05-06 23 06 31" src="https://user-images.githubusercontent.com/18254663/39674149-8cce1234-5182-11e8-9521-87265ba1364d.png">

#### Thermography
<img width="400" alt="2018-05-06 23 06 01" src="https://user-images.githubusercontent.com/18254663/39674148-8ca61dc4-5182-11e8-8bd9-f4f9c37836b9.png">

#### Posterization
<img width="400" alt="2018-05-06 23 05 02" src="https://user-images.githubusercontent.com/18254663/39674147-8c7c9abc-5182-11e8-8b45-cc9ff219a299.png">

## Reference
http://hooktail.org/computer/index.php?Bitmap%A5%D5%A5%A1%A5%A4%A5%EB%A4%F2%C6%FE%BD%D0%CE%CF%A4%B7%A4%C6%A4%DF%A4%EB
