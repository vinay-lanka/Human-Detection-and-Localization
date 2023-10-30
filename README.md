# Human-Detection-and-Localization

[![HDAL Tests](https://github.com/vinay-lanka/Human-Detection-and-Localization/actions/workflows/test.yaml/badge.svg)](https://github.com/vinay-lanka/Human-Detection-and-Localization/actions/workflows/test.yaml)
[![Codecov](https://codecov.io/gh/vinay-lanka/Human-Detection-and-Localization/graph/badge.svg?token=fQ4Z6RwMFH)](https://codecov.io/gh/vinay-lanka/Human-Detection-and-Localization)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)

**HDAL**: A robust perception stack for delivery robots to navigate sidewalks by detecting and localizing human obstacles.

This repository contains the deliverables for the Midterm Project of **Vikram Setty** (119696897) and **Vinay Lanka** (12041665) as a part of the course *ENPM808X: Software Development for Robotics* at the University of Maryland.

## Phase 2

### Project Overview
We present HDAL (Human Detection and Localization), a perception system for Acme Robotics’ delivery robot group. This project would give delivery robots the capability to detect and localize humans moving in front of them as they move on sidewalks delivering packages to the front doors of houses. The software would help the robot understand its surroundings and provide information to its path planners to choose an appropriate trajectory to move along.

HDAL is able to accomplish this using its two main components, its object detector and object tracker. While the object detector uses a YOLO v5 model to detect humans in the robot camera's field of view (FOV), the object tracker uses the detector's inferences to find the relative position of the human with respect to the robot's camera using geometric computer vision techniques. To do this, HDAL assumes a known fixed height of the robot's camera relative to the ground.

HDAL has a high level of performance. Even when executed on a laptop webcam using a CPU, it detects and tracks human presence and position in real-time with high accuracy. The latter sections of this file describe how to run the demo file of this project that allows you to do precisely that on your own system.

### About the Authors
The authors of HDAL are Vikram Setty and Vinay Lanka, both robotics graduate students at the University of Maryland.

Vikram is from Hyderabad, India, and has done his bachelor's and master's degrees with a major in mechanical engineering and a minor in computer science from IIT Ropar. His research interests include perception, navigation, and path planning for robotics and autonomous systems. He is also interested in various areas in artificial intelligence and machine learning, especially computer vision and reinforcement learning.

Vinay is from Hyderabad, India, and has done his bachelor's degree majoring in Electronics and Communication Engineering from VIT Vellore. He has two years of work experience in Robotics, having worked as a Robotics Engineer in Newspace Research and Technologies (Defence Aerospace) and as an R&D Engineer in Neoflux. He's interested in the areas of perception and planning of robots and also shares the common interest of Deep Learning and Computer Vision, especially in the field of Robotics.

### AIP Workflow Used
This project was developed using the Agile Development Process (AIP) along with pair programming (with a driver and navigator), with a focus on test-driven development (TDD). [This](https://docs.google.com/spreadsheets/d/1gvZUOzwOqA3FOt5ZHsv915nfBdFb774tYE5_qxB7flM/edit?usp=sharing) sheet has the product backlog, iteration backlogs, and work log for each task done to develop HDAL. The end of each iteration is even tagged to distinguish each sprint. Further, the link to the sprint planning and review meeting notes devised to overview each iteration sprint to develop HDAL in the most efficient way possible is attached [here](https://docs.google.com/document/d/1QYD2clcA70ukrI24V-6_yM0eB3UJxSPIeIFpcA2wneI/edit?usp=sharing).

The latest (Phase 2) developed UML class and activity diagrams can be found in the `UML/revised-phase-2` directory. The earlier devised UML diagrams as a part of Phase 1 and Phase 0 are available in the `UML/initial-phase-1` and `UML/initial-phase-0` directories. 

A short video providing a brief overview of the project and the details explaining the AIP process used is embedded below. A direct link to the same can also be found [here](https://www.youtube.com/watch?v=Eoj4YyOxvfU).

[![Video](https://i3.ytimg.com/vi/Eoj4YyOxvfU/maxresdefault.jpg)](https://www.youtube.com/watch?v=Eoj4YyOxvfU)

### Dependencies, Models, and Libraries
This project makes use of the OpenCV library (their official website can be found [here]()) for using computer vision functionalities and tools. HDAL also uses a YOLO v5 model (initially developed by Joseph Redmon, more information about which is linked [here](https://pjreddie.com/darknet/yolo/)). This deep-learning based object detection model helps HDAL detect humans from a continuous video feed from where further tracking is done. The YOLO v5 model is used by accessing its weights through a ONNX model that was generated from a PyTorch YOLO v5s model. This was done using [this](https://github.com/ultralytics/yolov5/releases) tutorial.

All of these libraries are integral to the working of HDAL and form a very important part of its mechansim. While OpenCV is fundamental to dealing with images (resizing, reshaping, scaling, formatting, etc), YOLO is the current benchmark for object detection and provides the best platform to track human coordinates from. Using the YOLO v5 model in an ONNX format is a good way to maintain uniformity and get access to easier methods and more flexible options in dealing with the model outputs on running object detection.

### Installing the Dependencies
To install the dependencies for this project (ONNX and OpenCV), simply run the command below on an Ubuntu system (confirmed to work on Ubuntu 22.04).
```sh
# Install OpenCV with root privileges (has the required headers for ONNX as well):
  sudo apt install libopencv-dev
```

### Building the Code

Before running any component of HDAL, make sure you are in the main working directory.
To build the project, execute the following commands.
```sh
# Create all the make files:
  cmake -S ./ -B build/
# Compile and build the code to the 'build' directory from scratch:
  cmake --build build/ --clean-first
# [When done with HDAL/need to rebuild] Clean the 'build' directory:
  cmake --build build/ --target clean
# [When done with HDAL/need to rebuild] Delete the 'build' directory:
  rm -rf build/
```

### Generating Documentation

To generate and view the Doxygen documentation of the project, run the following commands.
```sh
# Build the documentation into the 'docs' directory using CMake:
  cmake --build build/ --target docs
# Open the documentation as a HTML file in your web browser:
  open docs/html/index.html
```

### Running the Program Executables

To try a demo of HDAL on your system's webcam, execute the following commands. You should first know the input device `/dev/video0` in our case and measure the height of the camera. We will need this as command line arguments.
``` bash
# Execute the 'app/main.cpp' file to see a demo run of HDAL on your system's webcam:
  ./build/app/HDAL_demo '/dev/video0' 0.762
```

### Running Unit Tests

To manually run and verify the working of the unit tests for HDAL, execute the commands below.
``` bash
# Manually run the unit tests:
  ctest --test-dir build/
```

### Building for Test Coverage

This section shows how to configure the code to enable code coverage. Note that this information can also be viewed in the code coverage report which can be accessed by clicking the *codecov* badge at the top of this file. Otherwise, you can build the report manually and view the HTML file in a web browser by running the commands below.
```bash
# If you don't have gcovr or lcov installed, run:
  sudo apt-get install gcovr lcov
# Set the build type to Debug and WANT_COVERAGE=ON:
  cmake -D WANT_COVERAGE=ON -D CMAKE_BUILD_TYPE=Debug -S ./ -B build/
# Do a clean compile, run unit test, and generate the coverage report:
  cmake --build build/ --clean-first --target all test_coverage
# Open a web browser to browse the test coverage report:
  open build/test_coverage/index.html
```
Running these commands generates an `index.html` page in the `build/test_coverage` sub-directory that can be viewed on a local web browser.

You can also get a code coverage report for the *shell-app* target, instead of the unit tests. To do so, repeat the previous two steps, but with the *app_coverage* target:
``` bash
# Do another clean compile, run shell-app, and generate its coverage report:
  cmake --build build/ --clean-first --target all app_coverage
# Open a web browser to browse the test coverage report:
  open build/app_coverage/index.html
```

This generates an `index.html` page in the `build/app_coverage` sub-directory that can be viewed locally in a web browser.


### Google Coding Style Verification
To check how the written code conforms to the Google C++ style guide, look at the `results/cpplint_output.txt` file to see the output on using the *Cpplint* tool on this project. You should not be able to see any issues or problems, with all the files processed successfully.

This can be self-verified as well by running the following command in the highest-level directory of the project.
```sh
# Install Cpplint(ignore if already installed):
  sudo apt install cpplint
# Self-check Google code style conformity using Cpplint:
  cpplint --filter="-legal/copyright" $( find . -name *.cpp | grep -vE -e "^./build/" )
```

On running the above command, you should see the same output in the `results/cpplint_output.txt` file.


### Static Code Analysis
To check the static code analysis of this project, check the `results/cppcheck_output.txt` file to see the output on using the *Cppcheck* tool. You should not be able to see any issues or problems, with all the files checked successfully.

This can be self-verified as well by running the following command in the highest-level directory of the project.
```sh
# Install Cppcheck (ignore if already installed):
  sudo apt install cppcheck
# Self-check the static code analysis using Cppcheck:
  cppcheck --enable=all --std=c++11 --suppress=missingInclude $( find . -name *.cpp | grep -vE -e "^./build/" )
```

On running the above command, you should see the same output in the `results/cppcheck_output.txt` file.

## Phase 1

Phase 1 of the project involves building the directory structure, writing the class headers and stubs, and writing preliminary unit tests. It also involves getting GitHub Continuous Integration (CI), Code Coverage (codecov), and a license (MIT) along with their respective badges ready. All this is done using pair programming for test-driven development (TDD) using the Agile Iterative Process (AIP) software development model. 

A short video providing a brief overview of the first phase of the project and the details explaining the AIP process used is embedded below. A direct link to the same can also be found [here](https://www.youtube.com/watch?v=Eoj4YyOxvfU).

[![Video](https://i3.ytimg.com/vi/Eoj4YyOxvfU/maxresdefault.jpg)](https://www.youtube.com/watch?v=Eoj4YyOxvfU)

## Phase 0

Phase 0 involves the proposal for the project, along with information about the AIP model that would be used for software development in the project.

The Phase 0 project report, `proposal/Phase 0 Proposal.pdf` elicits the detailed plan, and vision, along with implementation specifics for the project. All aspects of the standard software plan are covered and explained in the analysis.

The quad chart for this project, `proposal/Phase 0 Quad Chart.pdf` describes the product, stakeholders, capabilities, and measures of success for the project. It is an important aspect of the Agile Iterative Process (AIP) methodology that would be followed throughout the duration of the project.

Further, a short video providing a brief overview of the project and the details explained in the report and quad chart is embedded below. To access the video directly from a link, please click [here](https://www.youtube.com/watch?v=uGA3f2nemRw).

[![Video](https://i3.ytimg.com/vi/uGA3f2nemRw/maxresdefault.jpg)](https://www.youtube.com/watch?v=uGA3f2nemRw)
