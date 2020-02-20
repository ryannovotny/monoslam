// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// JeVois Smart Embedded Machine Vision Toolkit - Copyright (C) 2016 by Laurent Itti, the University of Southern
// California (USC), and iLab at USC. See http://iLab.usc.edu and http://jevois.org for information about this project.
//
// This file is part of the JeVois Smart Embedded Machine Vision Toolkit.  This program is free software; you can
// redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software
// Foundation, version 2.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
// License for more details.  You should have received a copy of the GNU General Public License along with this program;
// if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
//
// Contact information: Laurent Itti - 3641 Watt Way, HNB-07A - Los Angeles, CA 90089-2520 - USA.
// Tel: +1 213 740 3527 - itti@pollux.usc.edu - http://iLab.usc.edu - http://jevois.org
// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file */

#include <jevois/Core/Module.H>
#include <jevois/Image/RawImageOps.H>

#include <Pangolin/include/pangolin/pangolin.h>
#include <SceneLib2/include/scenelib2/monoslam.h>
#include <SceneLib2/include/scenelib2/support/pangolin_util.h>

// icon by Catalin Fertu in cinema at flaticon

/*! 
    @author Ryan Novotny

    @videomapping YUYV 640 480 30.0 YUYV 640 480 30.0 JeVois MonoSLAM
    @email sampleemail\@samplecompany.com
    @address 123 First Street, Los Angeles, CA 90012
    @copyright Copyright (C) 2017 by Sample Author
    @mainurl http://samplecompany.com
    @supporturl http://samplecompany.com/support
    @otherurl http://samplecompany.com/about
    @license GPL v3
    @distribution Unrestricted
    @restrictions None */

class MonoSLAM : public jevois::Module
{
  private:
    SceneLib2::MonoSLAM *g_monoslam;
    // SceneLib2::Frame itsFrame;

    // pangolin::OpenGlRenderState view_state_3d();

  public:
    //! Constructor for SceneLib2
    MonoSLAM(std::string const & instance) : jevois::Module(instance)
    {
      g_monoslam = new SceneLib2::MonoSLAM();
      g_monoslam->Init("SceneLib2.cfg");

      // Define Camera Render Object (for view / scene browsing)
      // pangolin::OpenGlRenderState view_state_3d(pangolin::ProjectionMatrix(g_monoslam->camera_->width_,
      //                                                                   g_monoslam->camera_->height_,
      //                                                                    g_monoslam->camera_->fku_,
      //                                                                    g_monoslam->camera_->fkv_,
      //                                                                    g_monoslam->camera_->centre_(0),
      //                                                                    g_monoslam->camera_->centre_(1),
      //                                                                    0.00001, 1000),
      //                                          pangolin::ModelViewLookAt(-0.0, 0.18, -1.4, 0.0, 0.13, 0.0, pangolin::AxisY));
  
    }
    //! Default base class constructor ok
    using jevois::Module::Module;

    //! Virtual destructor for safe inheritance
    virtual ~MonoSLAM() { }

    // Create variables for SceneLib2
    bool  g_next = false;
    bool  g_play = false;
    int   g_frame_id  = 0;
    
    //! Processing function
    virtual void process(jevois::InputFrame && inframe, jevois::OutputFrame && outframe) override
    {
      // Wait for next available camera image:
      jevois::RawImage const inimg = inframe.get(true);

      // We only support YUYV pixels in this example, any resolution:
      inimg.require("input", inimg.width, inimg.height, V4L2_PIX_FMT_YUYV);

      // Convert to OpenCV image
      cv::Mat cvimg = jevois::rawimage::convertToCvRGB(inimg);

      // Begin SceneLib2 processing
      g_monoslam->GoOneStep(cvimg, false, false);
      
      // Wait for an image from our gadget driver into which we will put our results:
      jevois::RawImage outimg = outframe.get();

      // Enforce that the input and output formats and image sizes match:
      outimg.require("output", inimg.width, inimg.height, inimg.fmt);

      // Send cvimg for object drawing
      g_monoslam->graphic_tool_->DrawAR(cvimg, false, false, false,
                                        false, false, false, false);
      
      // Convert cvimg back to const
      jevois::RawImage rawimg;
      jevois::rawimage::convertCvRGBtoRawImage(cvimg, rawimg, 50);

      // Just copy over the image
      jevois::rawimage::paste(inimg, rawimg, 0, 0);
      
      // Print a text message:
      // jevois::rawimage::writeText(outimg, "Hello JeVois!", 100, 230, jevois::yuyv::White, jevois::rawimage::Font20x38);
      
      // Let camera know we are done processing the input image:
      inframe.done(); // NOTE: optional here, inframe destructor would call it anyway

      // Send the output image with our processing results to the host over USB:
      outframe.send(); // NOTE: optional here, outframe destructor would call it anyway
    }
};

// Allow the module to be loaded as a shared object (.so) file:
JEVOIS_REGISTER_MODULE(MonoSLAM);
