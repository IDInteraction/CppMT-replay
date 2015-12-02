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

static Scalar draw_colour(255, 255, 255);

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
  for(int i = 0; i < 4; i++) {
    int n = (i + 4) * 2;
    int m = (((i + 1) % 4) + 4) * 2;

    Point pnt1(bbox[n], bbox[n + 1]);
    Point pnt2(bbox[m], bbox[m + 1]);

    line(frame, pnt1, pnt2, draw_colour);
  }
}

void draw_bbox_centre(Mat frame, vector<float> bbox) {
  Point centre(bbox[3], bbox[4]);

  circle(frame, centre, 2, draw_colour);
}

string output_filename(string input_filename, string output_dir="") {
  int dot = input_filename.find_last_of('.');
  int out_len = output_dir.length();

  if(out_len > 0 && !(0 == output_dir.compare((out_len - 1), 1, "/"))) {
    output_dir += '/';
  }

  return output_dir + input_filename.substr(0, dot) + "_out.avi";
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
  VideoWriter out(output_filename(argv[1]), CV_FOURCC('X', 'V', 'I', 'D'), fps, size, true);
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
      draw_bbox_centre(image, bbox);
      bbox = get_next_line_tokens(csv);
    }

    out << image;
    frame++;
  }

  vid.release();
  out.release();

  return 0;
}
