# Human-Detection-and-Localization

**HDAL**: A robust perception stack for delivery robots to navigate sidewalks by detecting and localizing human obstacles.

This repository contains the deliverables for the Midterm Project of **Vikram Setty** (119696897) and **Vinay Lanka** (12041665) as a part of the course *ENPM808X: Software Development for Robotics* at the University of Maryland.

## Phase 1

### Project Overview
We present HDAL (Human Detection and Localization), a perception system for Acme Robotics’ delivery robot group. This project would give delivery robots the capability to detect and localize humans moving in front of them as they move on sidewalks delivering packages to the front doors of houses. The software would help the robot understand its surroundings and provide information to its path planners to choose an appropriate trajectory to move along.

HDAL is able to accomplish this using its two main components, its object detector and object tracker. While the object detector uses a YOLO v5 model to detect humans in the robot camera's field of view (FOV), the object tracker uses the detector's inferences to find the the relative position of the human with respect to the robot's camera using geometric computer vision techniques. To do this, HDAL assumes an known fixed height of the robot's camera relative to the ground.

HDAL has a high level of performance. Even when executed on a laptop webcame using a CPU, it detects and tracks human presence and position in real-time with high accuracy. The latter sections of this file describe how to run the demo file of this project that allows you to do precisely that on your own system.

### About the Authors
The authors of HDAL are Vikram Setty and Vinay Lanka, both robotics graduate students at the University of Maryland.

Vikram is from Hyderabad, India and has done his bachelor's and master's degree with a major in mechanical engineering and a minor in computer science from IIT Ropar. His research interests include perception, navigation and path planning for robotics and autonomous systems. He is also interested in various areas in artificial intelligence and machine learning, especially computer vision and reinforcement learning.

Vinay is from Hyderabad, India and has done his bachelor's degree majoring in Electronics and Communication Engineering from VIT Vellore. He has 2 years of work experience in Robotics, having worked as a Robotics Engineer in Newspace Research and Technologies (Defence Aerospace) and as a R&D Engineer in Neoflux. He's interested in the areas of perception and planning of robots and also shares the common interest of Deep Learning and Computer Vision, especially in the field of Robotics.

### AIP Workflow Used
This project was developed using the Agile Development Process (AIP) along with pair programming (with a driver and navigator), with a focus on test-driven development (TDD). [This](https://docs.google.com/spreadsheets/d/1gvZUOzwOqA3FOt5ZHsv915nfBdFb774tYE5_qxB7flM/edit?usp=sharing) sheet has the product backlog, iteration backlogs, and work log for each task done to develop HDAL. The end of each iteration is even tagged to distingish each sprint. Further, the link to the sprint planning and review meeting notes devised to overview each iteration sprint to develop HDAL in the most efficient way possible is attached [here](https://docs.google.com/document/d/1QYD2clcA70ukrI24V-6_yM0eB3UJxSPIeIFpcA2wneI/edit?usp=sharing).

The latest (Phase 1) developed UML class and actibity diagrams can be found in the `UML/initial-phase-1` directory. The earlier devised UML diagrams as a part of Phase 0 are available in the `UML/initial-phase-0` directory. 

A short video providing a brief overview of the project and the details explaining the AIP process used is embedded below. A direct link to the same can also be found [here]().

[![Video](https://i3.ytimg.com/vi/uGA3f2nemRw/maxresdefault.jpg)](https://www.youtube.com/watch?v=uGA3f2nemRw)

### Installing Dependencies
To install the dependencies for this project (ONNX, OpenCV, and Eigen), a thorough build and install of OpenCV followed y intsalling Eigen using the following commands should suffice (as per [OpenCV's](https://docs.opencv.org/4.x/d7/d9f/tutorial_linux_install.html) official website and [this](https://robots.uc3m.es/installation-guides/install-eigen.html) Eigen install tutorial). Make sure to run these commands outside this projcet's working directory in an Ubuntu system to prevent confusion with the project's 'build' directory.
```sh
# Prepare for the new installation of OpenCV by updating previous packages
  sudo apt update && sudo apt install -y cmake g++ wget unzip
# Download and unpack the new packages from the source
  wget -O opencv.zip https://github.com/opencv/opencv/archive/4.x.zip
unzip opencv.zip
# Create the 'build' directory:
  mkdir -p build && cd build
# Configure the package:
  cmake ../opencv-4.x
# Build the package:
  cmake --build .
# Build the package:
  sudo apt install libeigen3-dev
```

### Building the Code

Before running any component of HDAL, make sure you are in the main working directory.
To build the project, execute the following commands.
```sh
# Create all the make files:
  cmake -S ./ -B build/
# Compile and build the code to the 'build' directory from scratch:
  cmake --build build/ --clean-first
# Clean the 'build' directory:
  cmake --build build/ --target clean
# Remove the 'build' directory to rebuild the project if necessary:
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

To try a demo of HDAL on your system's webcam, execute the following commands.
``` bash
# Execute the 'app/main.cpp' file to see a demo run of HDAL on your system's webcam:
  ./build/app/HDAL_demo
```

### Runnning Unit Tests

To manually run and verify the working of the unit tests for HDAL, execute the commands below.
``` bash
# Manually run the unit tests:
  ctest --test-dir build/
```

### Building for Test Coverage

This sections shows how to configure the code to enable code coverage. Note that this information can also be viewed in the code coverage report which can be accessed by clicking the *codecov* badge on the top of this file. Otherwise, you can build the report manually and view the HTML file in a web browser by running the commands below.
```bash
# If you don't have gcovr or lcov installed, run:
  sudo apt-get install gcovr lcov
# Set the build type to Debug and WANT_COVERAGE=ON:
  cmake -D WANT_COVERAGE=ON -D CMAKE_BUILD_TYPE=Debug -S ./ -B build/
# Do a clean compile, run unit test, and generate the covereage report:
  cmake --build build/ --clean-first --target all test_coverage
# Open a web browser to browse the test coverage report:
  open build/test_coverage/index.html
```
Running these commands generates a `index.html` page in the `build/test_coverage` sub-directory that can be viewed on a local web browser.

You can also get code coverage report for the *shell-app* target, instead of the unit tests. To do so, repeat the previous last two steps, but with the *app_coverage* target:
``` bash
# Do another clean compile, run shell-app, and generate its covereage report:
  cmake --build build/ --clean-first --target all app_coverage
# Open a web browser to browse the test coverage report:
  open build/app_coverage/index.html
```

This generates a `index.html` page in the `build/app_coverage` sub-directory that can be viewed locally in a web browser.


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

## Phase 0

The Phase 0 project report, `Reports/Phase 0 Proposal.pdf` elicits the detailed plan, vision, along with implementation specifics for the project. All aspects of the standard software plan are covered and explained in the analysis.

The quad chart for this project, `Reports/Phase 0 Quad Chart.pdf`describes the product, stakeholders, capabilities, and measures of success for the project. It is an important aspect of the Agile Iterative Process (AIP) methodology that would be followed throughout the duration of the project.

Further, a short video providing a brief overview of the project and the details explained in the report and quad chart is embedded below.

[![Video](https://i3.ytimg.com/vi/uGA3f2nemRw/maxresdefault.jpg)](https://www.youtube.com/watch?v=uGA3f2nemRw)

To access the video directly from a link, please click [here](https://www.youtube.com/watch?v=uGA3f2nemRw).