# CppMT Replay

Robert Haines, University of Manchester, UK

## Synopsis

Combine [CppMT][cmt] object tracking data with the original video for verification and further use.

## Usage

This program takes a video and associated object tracking data output from [CppMT][cmt] (using the `--output-file` switch) and combines the two, overlaying the bounding box outline and centre point in the output video.

```shell
$ cmt-replay <video-input> <data-input>
```

The output video file is named automatically using the input video filename to ensure that a combination of codec and container that OpenCV can write to is used. For example, an input video file named `video.mp4` will produce an output video file named `video_out.avi`. OpenCV can read the mp4 container but cannot write to it.

## Acknowledgements

CppMT-replay was developed in the IDInteraction project, funded by the Engineering and Physical Sciences Research Council, UK through grant agreement number [EP/M017133/1][gow].

## Licence

Copyright (c) 2015 The University of Manchester, UK.

BSD Licenced. See LICENCE for details.

[cmt]: https://github.com/gnebehay/CppMT
[gow]: http://gow.epsrc.ac.uk/NGBOViewGrant.aspx?GrantRef=EP/M017133/1
