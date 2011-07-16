/*
 *  This file is part of RawTherapee.
 *
 *  Copyright (c) 2004-2010 Gabor Horvath <hgabor@rawtherapee.com>
 *
 *  RawTherapee is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 * 
 *  RawTherapee is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with RawTherapee.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <multilangmgr.h>
#include <toolpanelcoord.h>
#include <ilabel.h>
#include <options.h>
#include <imagesource.h>
#include <dfmanager.h>

using namespace rtengine::procparams;

ToolPanelCoordinator::ToolPanelCoordinator () : ipc(NULL)  {

    exposurePanel   = Gtk::manage (new Gtk::VBox ());
    detailsPanel    = Gtk::manage (new Gtk::VBox ());
    colorPanel      = Gtk::manage (new Gtk::VBox ());
    transformPanel  = Gtk::manage (new Gtk::VBox ());
    rawPanel        = Gtk::manage (new Gtk::VBox ());

    coarse              = Gtk::manage (new CoarsePanel ());
    curve               = Gtk::manage (new ToneCurve ());
    shadowshighlights   = Gtk::manage (new ShadowsHighlights ());
    //lumadenoise         = Gtk::manage (new LumaDenoise ());
    //colordenoise        = Gtk::manage (new ColorDenoise ());
    impulsedenoise      = Gtk::manage (new ImpulseDenoise ());
    defringe            = Gtk::manage (new Defringe ());
    dirpyrdenoise       = Gtk::manage (new DirPyrDenoise ());
    sharpening          = Gtk::manage (new Sharpening ());
    lcurve              = Gtk::manage (new LCurve ());
    //colorboost          = Gtk::manage (new ColorBoost ());
    //colorshift          = Gtk::manage (new ColorShift ());
    lensgeom            = Gtk::manage (new LensGeometry ());
    distortion          = Gtk::manage (new Distortion ());
    rotate              = Gtk::manage (new Rotate ());
    whitebalance        = Gtk::manage (new WhiteBalance ());
    vignetting          = Gtk::manage (new Vignetting ());
    perspective         = Gtk::manage (new PerspCorrection ());
    cacorrection        = Gtk::manage (new CACorrection ());
    hlrecovery          = Gtk::manage (new HLRecovery ());
    chmixer             = Gtk::manage (new ChMixer ());
    resize              = Gtk::manage (new Resize ());
    crop                = Gtk::manage (new Crop ());
    icm                 = Gtk::manage (new ICMPanel ());
    exifpanel           = Gtk::manage (new ExifPanel ());
    iptcpanel           = Gtk::manage (new IPTCPanel ());
    //equalizer           = Gtk::manage (new Equalizer ());
    dirpyrequalizer     = Gtk::manage (new DirPyrEqualizer ());
    hsvequalizer        = Gtk::manage (new HSVEqualizer ());
    rawprocess          = Gtk::manage (new RawProcess ());
    preprocess          = Gtk::manage (new PreProcess ());
    darkframe           = Gtk::manage (new DarkFrame ());
    rawcacorrection     = Gtk::manage (new RAWCACorr ());
    rawexposure         = Gtk::manage (new RAWExposure ());

    addPanel (colorPanel, whitebalance,         M("TP_WBALANCE_LABEL"));       toolPanels.push_back (whitebalance);
    addPanel (exposurePanel, curve,             M("TP_EXPOSURE_LABEL"));       toolPanels.push_back (curve);
    addPanel (exposurePanel, hlrecovery,        M("TP_HLREC_LABEL"));          toolPanels.push_back (hlrecovery);
    addPanel (colorPanel, chmixer,              M("TP_CHMIXER_LABEL"));        toolPanels.push_back (chmixer);
    addPanel (exposurePanel, shadowshighlights, M("TP_SHADOWSHLIGHTS_LABEL")); toolPanels.push_back (shadowshighlights);
    addPanel (detailsPanel, sharpening,         M("TP_SHARPENING_LABEL"));     toolPanels.push_back (sharpening);
    //addPanel (colorPanel, colorboost,           M("TP_COLORBOOST_LABEL"));     toolPanels.push_back (colorboost);
    //addPanel (colorPanel, colorshift,           M("TP_COLORSHIFT_LABEL"));     toolPanels.push_back (colorshift);
    addPanel (colorPanel, hsvequalizer,         M("TP_HSVEQUALIZER_LABEL"));   toolPanels.push_back (hsvequalizer);
    addPanel (exposurePanel, lcurve,            M("TP_LABCURVE_LABEL"));	   toolPanels.push_back (lcurve);
    addPanel (detailsPanel, impulsedenoise,     M("TP_IMPULSEDENOISE_LABEL")); toolPanels.push_back (impulsedenoise);
    //addPanel (detailsPanel, lumadenoise,        M("TP_LUMADENOISE_LABEL"));    toolPanels.push_back (lumadenoise);
    //addPanel (detailsPanel, colordenoise,       M("TP_COLORDENOISE_LABEL"));   toolPanels.push_back (colordenoise);
    addPanel (detailsPanel, dirpyrdenoise,      M("TP_DIRPYRDENOISE_LABEL"));  toolPanels.push_back (dirpyrdenoise);
    addPanel (detailsPanel, defringe,           M("TP_DEFRINGE_LABEL"));	   toolPanels.push_back (defringe);
    addPanel (detailsPanel, dirpyrequalizer,    M("TP_DIRPYREQUALIZER_LABEL"));	toolPanels.push_back (dirpyrequalizer);
    //addPanel (detailsPanel, equalizer,          M("TP_EQUALIZER_LABEL"));      toolPanels.push_back (equalizer);
    addPanel (transformPanel, crop,             M("TP_CROP_LABEL"));           toolPanels.push_back (crop);
    addPanel (transformPanel, resize,           M("TP_RESIZE_LABEL"));         toolPanels.push_back (resize);
    addPanel (transformPanel, lensgeom,         M("TP_LENSGEOM_LABEL"));       toolPanels.push_back (lensgeom);
    addPanel (lensgeom->getPackBox(), rotate,       M("TP_ROTATE_LABEL"));       toolPanels.push_back (rotate);
    addPanel (lensgeom->getPackBox(), perspective,  M("TP_PERSPECTIVE_LABEL"));  toolPanels.push_back (perspective);
    addPanel (lensgeom->getPackBox(), distortion,   M("TP_DISTORTION_LABEL"));   toolPanels.push_back (distortion);
    addPanel (lensgeom->getPackBox(), cacorrection, M("TP_CACORRECTION_LABEL")); toolPanels.push_back (cacorrection);
    addPanel (lensgeom->getPackBox(), vignetting,   M("TP_VIGNETTING_LABEL"));   toolPanels.push_back (vignetting);
    addPanel (colorPanel, icm,                  M("TP_ICM_LABEL"));             toolPanels.push_back (icm);
    addPanel (rawPanel, rawprocess,             M("TP_RAW_LABEL"));            toolPanels.push_back (rawprocess);
    addPanel (rawPanel, preprocess,             M("TP_PREPROCESS_LABEL"));     toolPanels.push_back (preprocess);
    addPanel (rawPanel, rawexposure,            M("TP_EXPOSCORR_LABEL"));      toolPanels.push_back (rawexposure);
    addPanel (rawPanel, darkframe,              M("TP_DARKFRAME_LABEL"));      toolPanels.push_back (darkframe);
    addPanel (rawPanel, rawcacorrection,        M("TP_CHROMATABERR_LABEL"));   toolPanels.push_back (rawcacorrection);

    toolPanels.push_back (coarse);
    toolPanels.push_back (exifpanel);
    toolPanels.push_back (iptcpanel);

    metadataPanel = Gtk::manage (new Gtk::Notebook ());
    toolPanelNotebook = new Gtk::Notebook ();

    metadataPanel->append_page (*exifpanel, M("MAIN_TAB_EXIF"));
    metadataPanel->append_page (*iptcpanel, M("MAIN_TAB_IPTC"));

    Gtk::ScrolledWindow* exposurePanelSW    = Gtk::manage (new Gtk::ScrolledWindow ());
    Gtk::ScrolledWindow* detailsPanelSW     = Gtk::manage (new Gtk::ScrolledWindow ());
    Gtk::ScrolledWindow* colorPanelSW       = Gtk::manage (new Gtk::ScrolledWindow ());
    Gtk::ScrolledWindow* transformPanelSW   = Gtk::manage (new Gtk::ScrolledWindow ());
    Gtk::ScrolledWindow* rawPanelSW         = Gtk::manage (new Gtk::ScrolledWindow ());
    exposurePanelSW->set_policy     (Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    detailsPanelSW->set_policy      (Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    colorPanelSW->set_policy        (Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    transformPanelSW->set_policy    (Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    rawPanelSW->set_policy          (Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

    exposurePanelSW->add  (*exposurePanel);
    detailsPanelSW->add   (*detailsPanel);
    colorPanelSW->add     (*colorPanel);
    transformPanelSW->add (*transformPanel);
    rawPanelSW->add       (*rawPanel);

    toolPanelNotebook->append_page (*exposurePanelSW,  M("MAIN_TAB_EXPOSURE"));
    toolPanelNotebook->append_page (*detailsPanelSW,   M("MAIN_TAB_DETAIL"));
    toolPanelNotebook->append_page (*colorPanelSW,     M("MAIN_TAB_COLOR"));
    toolPanelNotebook->append_page (*transformPanelSW, M("MAIN_TAB_TRANSFORM"));
    toolPanelNotebook->append_page (*rawPanelSW,       M("MAIN_TAB_RAW"));
    toolPanelNotebook->append_page (*metadataPanel,    M("MAIN_TAB_METADATA"));
    toolPanelNotebook->set_current_page (0);

    toolPanelNotebook->set_scrollable ();
    toolPanelNotebook->show_all ();

    for (int i=0; i<toolPanels.size(); i++)
        toolPanels[i]->setListener (this);

    whitebalance->setWBProvider (this);
    whitebalance->setSpotWBListener (this);
    lensgeom->setLensGeomListener (this);
    rotate->setLensGeomListener (this);
    crop->setCropPanelListener (this);
    icm->setICMPanelListener (this);

    toolBar = new ToolBar ();
}

void ToolPanelCoordinator::addPanel (Gtk::Box* where, FoldableToolPanel* panel, Glib::ustring label) {

    if (where->children().size()) {
        Gtk::HSeparator *hsep = Gtk::manage (new  Gtk::HSeparator());
        where->pack_start(*hsep, Gtk::PACK_SHRINK, 0);
        hsep->show();
    }

    panel->setParent(where);
    panel->setLabel(label);

	expList.push_back (panel->exp);
    where->pack_start(*panel->exp, false, false);
}

ToolPanelCoordinator::~ToolPanelCoordinator () {

    closeImage ();

    delete toolPanelNotebook;
    delete toolBar;
}

void ToolPanelCoordinator::panelChanged (rtengine::ProcEvent event, const Glib::ustring& descr) {

    if (!ipc) return;

    ProcParams* params = ipc->getParamsForUpdate (event);
    for (int i=0; i<toolPanels.size(); i++)
        toolPanels[i]->write (params);

    // some transformations make the crop change for convenience
    if (event==rtengine::EvCTHFlip) {
        crop->hFlipCrop ();
        crop->write (params);
    }
    else if (event==rtengine::EvCTVFlip) {
        crop->vFlipCrop ();
        crop->write (params);
    }
    else if (event==rtengine::EvCTRotate) {
        crop->rotateCrop (params->coarse.rotate);
        crop->write (params);
        resize->update (params->crop.enabled, params->crop.w, params->crop.h, ipc->getFullWidth(), ipc->getFullHeight());
        resize->write (params);
    }
    else if (event==rtengine::EvCrop) {
        resize->update (params->crop.enabled, params->crop.w, params->crop.h);
        resize->write (params);
    }

    ipc->paramsUpdateReady ();

    hasChanged = true;

    for (int i=0; i<paramcListeners.size(); i++)
        paramcListeners[i]->procParamsChanged (params, event, descr);
}

void ToolPanelCoordinator::profileChange  (const ProcParams *nparams, rtengine::ProcEvent event, const Glib::ustring& descr, const ParamsEdited* paramsEdited) {

	int fw, fh, tr;

    if (!ipc) return;
    ProcParams *params = ipc->getParamsForUpdate (event);
    *params = *nparams;

    tr = TR_NONE;
    if (params->coarse.rotate==90)  tr |= TR_R90;
    if (params->coarse.rotate==180) tr |= TR_R180;
    if (params->coarse.rotate==270) tr |= TR_R270;

    // trimming overflowing cropped area
    rtengine::ImageSource *ii = (rtengine::ImageSource*)ipc->getInitialImage();
    ii->getFullSize (fw, fh, tr);
    crop->trim(params, fw, fh);

    // updating the GUI with updated values
    for (unsigned int i=0; i<toolPanels.size(); i++)
        toolPanels[i]->read (params);

    ipc->paramsUpdateReady ();

    hasChanged = event != rtengine::EvProfileChangeNotification;

    for (int i=0; i<paramcListeners.size(); i++)
        paramcListeners[i]->procParamsChanged (params, event, descr);
}

void ToolPanelCoordinator::setDefaults (ProcParams* defparams) {

    if (defparams)
        for (int i=0; i<toolPanels.size(); i++) 
            toolPanels[i]->setDefaults (defparams);
}

CropGUIListener* ToolPanelCoordinator::getCropGUIListener () {

    return crop;
}

void ToolPanelCoordinator::initImage (rtengine::StagedImageProcessor* ipc_, bool raw) {

    ipc = ipc_;
    curve->disableListener ();
    curve->enableAll ();
    curve->enableListener ();


    exifpanel->setImageData (ipc->getInitialImage()->getMetaData());
    iptcpanel->setImageData (ipc->getInitialImage()->getMetaData());

    if (ipc) {
        ipc->setAutoExpListener (curve);
        ipc->setSizeListener (crop);
        ipc->setSizeListener (resize);
    }

    icm->setRaw (raw); 
    hlrecovery->setRaw (raw);
    hasChanged = true;
}


void ToolPanelCoordinator::closeImage () {

    if (ipc) {
        ipc->stopProcessing ();        
        ipc = NULL;
    }
}

void ToolPanelCoordinator::readOptions () {

    crop->readOptions (); 
    for (int i=0; i<options.tpOpen.size(); i++)
        if (i<expList.size())
            expList[i]->set_expanded (options.tpOpen[i]);

    //if (options.crvOpen.size()>1)
    //    curve->expandCurve (options.crvOpen[0]);
}

void ToolPanelCoordinator::writeOptions () { 

    crop->writeOptions (); 
    options.tpOpen.clear ();
    for (int i=0; i<expList.size(); i++)
        options.tpOpen.push_back (expList[i]->get_expanded ());

    //options.crvOpen.clear ();
    //options.crvOpen.push_back (curve->isCurveExpanded());
}


void ToolPanelCoordinator::cropSelectionReady () {

  toolBar->setTool (TMHand);

  if (!ipc)
    return;
}

void ToolPanelCoordinator::rotateSelectionReady (double rotate_deg, Thumbnail* thm) {

  toolBar->setTool (TMHand);

  if (!ipc)
    return;

  if (rotate_deg!=0.0)
      rotate->straighten (rotate_deg);
}

void ToolPanelCoordinator::spotWBselected (int x, int y, Thumbnail* thm) {

    if (!ipc)
        return;

//    toolBar->setTool (TOOL_HAND);
    if (x>0 && y>0) {
        double temp;
        double green;
        ipc->getSpotWB (x, y, whitebalance->getSize (), temp, green);
        whitebalance->setWB (temp, green);
    }
}

void ToolPanelCoordinator::autoCropRequested () {

    if (!ipc)
        return;
        
    int x1, y1, x2, y2, w, h;
    ipc->getAutoCrop (crop->getRatio(), x1, y1, w, h);
    x2 = x1 + w - 1;
    y2 = y1 + h - 1;
    crop->cropInit (x1, y1, w, h);
    crop->cropResized (x1, y1, x2, y2);
    crop->cropManipReady ();
}

void ToolPanelCoordinator::straightenRequested () {

    if (!ipc)
        return;

    toolBar->setTool (TMStraighten);
}

void ToolPanelCoordinator::spotWBRequested (int size) {

    if (!ipc)
        return;

    toolBar->setTool (TMSpotWB);
}

void ToolPanelCoordinator::cropSelectRequested () {

    if (!ipc)
        return;

    toolBar->setTool (TMCropSelect);
}

void ToolPanelCoordinator::saveInputICCReference (Glib::ustring fname) {

    if (ipc)
        ipc->saveInputICCReference (fname);
}

int ToolPanelCoordinator::getSpotWBRectSize () {

    return whitebalance->getSize ();
}

void ToolPanelCoordinator::updateCurveBackgroundHistogram (unsigned* histrgb, unsigned* histl) {

    curve->updateCurveBackgroundHistogram (histrgb);
    lcurve->updateCurveBackgroundHistogram (histl);
}

void ToolPanelCoordinator::foldAllButOne (Gtk::Box* parent, FoldableToolPanel* openedSection) {

	FoldableToolPanel* currentTP;

    for (int i=0; i<toolPanels.size(); i++) {
        currentTP = (FoldableToolPanel*)toolPanels[i];
        if (currentTP->getParent() == parent) {
            // Section in the same tab, we unfold it if it's not the one that has been clicked
            if (currentTP != openedSection) {
                currentTP->exp->set_expanded(false);
            }
            else {
                if (!currentTP->exp->get_expanded())
                    currentTP->exp->set_expanded(true);
            }
        }
    }
}
