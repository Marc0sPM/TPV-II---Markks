// This file is part of the course TPV2@UCM - Samir Genaim

#include "ImageWithFrames.h"

#include <string>
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include "Transform.h"

ImageWithFrames::ImageWithFrames(Texture *tex, int cols, int rows, int x, int y,
		int fW, int fH, int scol, int srow, int ncol, int nrow, Uint32 timeBetweenFrames) :
		tex_(tex), //
		tr_(nullptr), //
		currFrameR_(0), //
		currFrameC_(0), //
		x_(x), //
		y_(y), //
		frameWidth_(fW), //
		frameHeight_(fH), //
		srow_(srow), //
		scol_(scol), //
		nrow_(nrow), //
		ncol_(ncol), //
		timeBetweenFrames_(timeBetweenFrames), //
		lastFrameChange_(0)
{
}

ImageWithFrames::~ImageWithFrames() {
}

void ImageWithFrames::initComponent() {
	tr_ = mngr_->getComponent<Transform>(ent_);
	assert(tr_ != nullptr);
}

void ImageWithFrames::render() {
	if (sdlutils().virtualTimer().currTime() > lastFrameChange_ + timeBetweenFrames_) {
		lastFrameChange_ = sdlutils().virtualTimer().currTime();
		currFrameC_ = (currFrameC_ + 1) % ncol_;
		if (currFrameC_ == 0)
			currFrameR_ = (currFrameR_ + 1) % nrow_;
	}

	int r = (currFrameR_ + srow_);
	int c = (currFrameC_ + scol_);
	auto src = build_sdlrect(c * frameWidth_ + x_, r * frameHeight_ + y_, frameWidth_,
			frameHeight_);

	auto dest = build_sdlrect(tr_->pos_, tr_->width_, tr_->height_);

	tex_->render(src, dest, tr_->rot_);

}
