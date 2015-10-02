/*
-------------------------------------------------------------------------------
 Copyright (c) 2015 The University of Manchester, UK.

 BSD Licenced. See LICENCE for details.

 CppMT-replay was developed in the IDInteraction project, funded by the
 Engineering and Physical Sciences Research Council, UK through grant
 agreement number EP/M017133/1.

 Author: Robert Haines
-------------------------------------------------------------------------------
*/

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>

#include <opencv2/highgui/highgui.hpp>

using cv::Mat;
using cv::Point;
using cv::Scalar;
using cv::Size;
using cv::VideoCapture;
using cv::VideoWriter;

using std::atof;
using std::cerr;
using std::endl;
using std::getline;
using std::ifstream;
using std::istream;
using std::string;
using std::stringstream;
using std::vector;

vector<float> get_next_line_tokens(istream& file_stream) {
  vector<float> tokens;
  string line;
  getline(file_stream, line);
  stringstream line_stream(line);
  string cell;

  while(getline(line_stream, cell, ',')) {
    tokens.push_back(atof(cell.c_str()));
  }

  return tokens;
}

void draw_bbox(Mat frame, vector<float> bbox) {
  Point point1(bbox[8], bbox[9]);
  Point point2(bbox[10], bbox[11]);
  Point point3(bbox[12], bbox[13]);
  Point point4(bbox[14], bbox[15]);

  line(frame, point1, point2, Scalar(255,0,0));
  line(frame, point2, point3, Scalar(255,0,0));
  line(frame, point3, point4, Scalar(255,0,0));
  line(frame, point4, point1, Scalar(255,0,0));
}

int main(int argc, char **argv) {

  // Open input video file and interrogate it.
  VideoCapture vid(argv[1]);
  if(!vid.isOpened()) {
    cerr << "Cannot open input video." << endl;
    return 1;
  }
  double fps = vid.get(CV_CAP_PROP_FPS);
  Size size((int) vid.get(CV_CAP_PROP_FRAME_WIDTH), (int) vid.get(CV_CAP_PROP_FRAME_HEIGHT));

  // Open input CSV file and throw away header line.
  ifstream csv(argv[2]);
  get_next_line_tokens(csv);

  // Open output video file.
  VideoWriter out(argv[3], CV_FOURCC('X', 'V', 'I', 'D'), fps, size, true);
  if(!out.isOpened()) {
    cerr << "Cannot open output video." << endl;
    return 1;
  }

  Mat image;
  int frame = 0;
  vector<float> bbox = get_next_line_tokens(csv);

  while(true) {
    vid >> image;
    if(image.empty()) break;

    // If we have bbox data and it's for the right frame...
    if(bbox.size() > 0 && bbox[0] == frame) {
      draw_bbox(image, bbox);
      bbox = get_next_line_tokens(csv);
    }

    out << image;
    frame++;
  }

  vid.release();
  out.release();

  return 0;
}
