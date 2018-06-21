/** \file
 */

#include "Badge.h"
#include "matrixAnimation.h"
#include "matrixScroller.h"
#include "frame-usaflagwave.h"
#include "frame-saturn5.h"
#include "frame-boobies.h"

Badge badge;

const uint8_t DEMO_USAFLAG = 0;
const uint8_t DEMO_SCROLLER = 1;
const uint8_t DEMO_SATURN5 = 2;
const uint8_t num_demos = 3;
const uint8_t DEMO_BOOBIES = 99;  // not part of normal rotation

// runtime variables
uint8_t cur_demo = DEMO_USAFLAG;
uint32_t last_draw_millis;
uint32_t update_frequency;

uint8_t flagreps_cur = 0;
#define FLAGREPS_TOTAL 6

uint8_t boobreps_cur = 0;
#define BOOBREPS_TOTAL 3

MatrixScroller scroller(" Happy July 4th!  ");

void setup()
{
    badge.begin();
    badge.matrix.setBrightness(100);
}

void loop()
{
  // display the sample animation
  const uint32_t now = millis();

  if (now - last_draw_millis < update_frequency)
    return;
  last_draw_millis = now;

  if (badge.button_edge()) {
    cur_demo = DEMO_BOOBIES;
  }

  if(cur_demo == DEMO_USAFLAG) {
    update_frequency = usaflag_animation.getFrameDelay();
    // draw the next frame of the animation
    usaflag_animation.draw(badge.matrix);
    if(usaflag_animation.getFrameIndex() == 0) {
      // the animation has completed one play-through, repeat it
      flagreps_cur++;
      if(flagreps_cur == FLAGREPS_TOTAL) {
        // completed all repetitions, go to the next demo
        flagreps_cur = 0;
        cur_demo++;
      }
    }
  } else if(cur_demo == DEMO_SCROLLER) {
    update_frequency = 80; // update every Xms
    scroller.draw(badge.matrix);
    if(scroller.getPosition() == 0) {
      // the scroller has completed one play-through, switch to the next demo
      cur_demo++;
    }
  } else if (cur_demo == DEMO_SATURN5) {
    update_frequency = animation_saturn5.getFrameDelay();
    // draw the next frame of the animation
    animation_saturn5.draw(badge.matrix);
    if(animation_saturn5.getFrameIndex() == 0) {
      // the animation has completed one play-through, switch to the next demo
      cur_demo++;
    }
  } else if(cur_demo == DEMO_BOOBIES) {
    update_frequency = boobies_animation.getFrameDelay();
    boobies_animation.draw(badge.matrix);
    if(boobies_animation.getFrameIndex() == 0) {
      // the animation has completed one play-through, repeat it
      boobreps_cur++;
      if(boobreps_cur == BOOBREPS_TOTAL) {
        // completed all repetitions, go back to the regular demos
        boobreps_cur = 0;
        cur_demo = DEMO_USAFLAG;
      }
    }
  }

  // wrap around if we've played all the demos
  if(cur_demo == num_demos)
    cur_demo = 0;
}




