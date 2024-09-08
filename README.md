# PolygonDust

## Description

PolygonDust is an application to measure the area size of polygon, or execute bitwise operator on two or more polygon.

PolygonDust expect to support images like PNG/JPG. Split the image to lot of square, and determine the area of polygon by how many square is not white. Moreover, by the square can record the specific area is the part of shape or not, we can doing some bitwise opearation on square status and make a bitwise-operated images.



## Problem to Solve 

PolygonDust is used to solve the shape union/difference by pixel-way. We use image process instead of formula to describe the shape, but it may easier to solve the problem.



The benefit of solve shape union/difference by pixel-way:

- Straightful and union way to find out the size of shapes union/difference.
- Easy to output the result images (without lot of equation and need to visualize the shape draw by equation).
- Easy to process the images. Python package can process the image easily.



The disadventage of solve shape union/difference by pixel-way:

- Have **more** error rate than equation-way.
- Affected by the image resolution.



In this project, we are focus on "how numerical software can solve this problem" and "Trying to make a nice application with these result which process by numerical software". 

The numerical software may solve the image processing with these steps:

- [Gaussian Blur](https://zh.wikipedia.org/zh-tw/%E9%AB%98%E6%96%AF%E6%A8%A1%E7%B3%8A) to decrease the noice.
- Binarization: We trying to use [Otsu's method](https://zh.wikipedia.org/wiki/%E5%A4%A7%E6%B4%A5%E7%AE%97%E6%B3%95), it calculate the threadhold globally, and may have more efficiency to process binarization.
- Cut the image to lot of piece
- Process these piece by determine the piece is fill/not fill, and vote 0/1.
- By the result of voting, calculate the area of image, or process bitwise operation on these images.



## Prospective Users

The user should know how to use command-line interface. Which a communication way to process PolygonDust. In PolygonDust, we *try out best* to make  or command easy to know, and provide a nice log to show the process or result.



## System Architecture / API Description

*Since I still don't know what the proper way to communicate between Python and C++, I'll trying to use command-line process the flow. But It will be good to know more proper way to optimize the flow.*

In this project, we will split into three part:

- Processor 1: Gaussian Blur utility. 
  - It can input the image with command line to execute the utility and output the result. Write in C++.
  - Example: `pd-gb -i polygon.png -o polygon-gb.png`
- Processor 2: Otsu's method utility. 
  - It can input the image with command line to execute the utility and output the result. Write in C++.
  - Example: `pd-om -i polygon-gb.png -o polygon-gb-om.png`
- Processor 3: Controller. 
  - Trying to execute the utility in Python, cut the image into pieces, handling vote for pieces, and output the result.
  - The User should process the numerical software by this controller, but we are not rule out the user execute the utility if they need it.
  - Example: `./polygonDust -i polygon1.png --xor -i polygon2.png --and -i polygon3.png -o polygon-result.png --particles 5`
    - We input `polygon1.png` as a first images
    - We input `polygon2.png` as a second image and should do XOR operator with first image.
    - We input `polygon3.png` as a third image and should do AND operator with pervious result.
    - We output result to `polygon-result.png`
    - The particles is `5px` for images, means it should split the images into lot of 5x5 square



The Numerical process flow should be like this:

![image-20240909022525138](/Users/xuan/Library/Application Support/typora-user-images/image-20240909022525138.png)



## Engineering Infrastructure

I list a few engineering infrastructure, but it may change if we need.

- For easy to develop, easy to add dependency, and easy to make error message more straighful, we will use CMake to build or project.
- We use git to do some version control, and push our source code to GitHub. The project is open source with MIT license.
- We use GitHub Action to check the project can build property in every commit.
- Write some test with gtest if we need it, and it may using `valgrind` to track memory leak or using `gcovr` to know the test coverage.
- A Good `README.md` to know how to install this project and how to use this project.

We also trying to obey OOP principle to optimize our code quality >:)



## Feature Request

Split into three part.

- Worker `PD-GB`
  - Have a command-line interface to input the data.
  - Output the result image.
  - It should do Gaussing Blur in this worker.
- Worker `PD-OM`
  - Have a command-line interface to input the data.
  - Output the result image.
  - It should do Otsu's method in this worker.
- Controller
  - Have a command-line interface to input the data.
  - Can execute the worker to do calculation.
  - Can shred the image into lot of pieces.
  - Can handle voting for these pieces.
  - Can create bitwise-operation and output desired polygon.
  - Can output the area information of polygon.



## Schedule

| Week |                             Task                             | Progress (%) |
| :--: | :----------------------------------------------------------: | :----------: |
|  1   |               System Design / Writing proposal               |  0% (0/12)   |
|  2   | Create GitHub Project, trying to figure how to process image on C++, and how to process command line interface on C++. |  0% (0/12)   |
|  3   | Trying to complete the "shell" of PD-GB and PD-OM. We complete the command line interface but not implement the calculation feature. | 17% (02/12)  |
|  4   |    Trying to implement the calculation feature of PD-GB.     | 17% (02/12)  |
|  5   |    Trying to implement the calculation feature of PD-GB.     | 33% (04/12)  |
|  6   |    Trying to implement the calculation feature of PD-OM.     | 33% (04/12)  |
|  7   |    Trying to implement the calculation feature of PD-OM.     | 50% (06/12)  |
|  8   |            Check PD-GB and PD-OM is work property            | 50% (06/12)  |
|  9   |         Trying to implement the shell of controller.         | 58% (07/12)  |
|  10  | Trying to implement the execution phase of controller to execute the worker. | 67% (08/12)  |
|  11  | Implement shred feature to split the image with specific size of square. | 75% (09/12)  |
|  12  |   Trying to implement the voting feature of these squares.   | 83% (10/12)  |
|  13  | Trying to implement bitwise-operation and output desired image. | 92% (11/12)  |
|  14  | Trying to output desired image based on the result of bitwise-operation. | 100% (12/12) |
|  15  | Everything work! The future task will be optimize the software by parallel or some trick if time allow. |   300%​ :)    |

