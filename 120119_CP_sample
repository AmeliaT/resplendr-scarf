# CircuitPython code for Resplendr Scarf using FancyLED,
# which utilizes a strip of 50 NeoPixels, an Adafruit Gemma M0, 
# and a tactile button to navigate modes. Use JST LiPoly or USB power bank. 
#
# Full build information, build kits, and finished products available via www.resplendr.com
#
# Ensure that you have the latest updates for CP
# Download the uf2 of CP for Gemma M0:  https://circuitpython.org/board/gemma_m0/
# upload to gemmaboot
# Download the latest CP bundle that matches the latest version on the board 
# https://circuitpython.org/libraries
# 
# Create lib folder and add only these from the bundle: 
# adafruit_fancyled
# &
# neopixel.mpy
# 
# add below to Gemma in main.py file. 
# Recommended to use mu-editor


import adafruit_fancyled.adafruit_fancyled as fancy
import board
import neopixel
from digitalio import DigitalInOut, Direction, Pull

led_pin = board.D0  # which pin your pixels are connected to
num_leds = 50  # how many LEDs you have
brightness = 1.0  # 0-1, higher number is brighter
saturation = 255  # 0-255, 0 is pure white, 255 is fully saturated color
steps = 0.01  # how wide the bands of color are.
offset = 0  # cummulative steps
fadeup = True  # start with fading up - increase steps until offset reaches 1
index = 8  # midway color selection
blend = True  # color blending between palette indices

# initialize list with all pixels off
palette = [0] * num_leds

# Declare a NeoPixel object on led_pin with num_leds as pixels
# No auto-write.
# Set brightness to max.
# We will be using FancyLED's brightness control.
strip = neopixel.NeoPixel(led_pin, num_leds, brightness=1, auto_write=False)

# button setup
button = DigitalInOut(board.D2)
button.direction = Direction.INPUT
button.pull = Pull.UP
prevkeystate = False
ledmode = 0  # button press counter, switch color palettes

# FancyLED allows for assigning a color palette using these formats:
# * The first (5) palettes here are mixing between 2-elements
# * The last (3) palettes use a format identical to the FastLED Arduino Library
# see FastLED - colorpalettes.cpp

all_colors = [fancy.CRGB(0, 0, 0),  # black
              fancy.CRGB(255, 255, 255)]  # white

allRed = [fancy.CRGB(255, 0, 0)] #red

allGold = [0xFFD700] #gold

allPurple = [fancy.CRGB(160, 32, 240)] #purple

galaxy = [0x191970, 0x4B0082, 0x000000, 0x000000,
          0x000080, 0x008080, 0x000000, 0x000000,
          0x008080, 0x4B0082, 0x000000, 0x000000,
          0x000080, 0x008080, 0x000000, 0x000000]

mermaid = [0x1E90FF, 0x00008B, 0x008080, 0x4B0082,
           0x1E90FF, 0x00008B, 0x40E0D0, 0x8A2BE2,
           0x1E90FF, 0x00008B, 0x008080, 0x8A2BE2,
           0x1E90FF, 0x00008B, 0x40E0D0, 0x4B0082]

sunset = [fancy.CRGB(220,20,60),
  fancy.CRGB(128,0,0),
  fancy.CRGB(255,0,0),
  fancy.CRGB(255,69,0),
 
  fancy.CRGB(220,20,60),
  fancy.CRGB(128,0,0),
  fancy.CRGB(255,0,0),
  fancy.CRGB(255,69,0),
 
  fancy.CRGB(220,20,60),
  fancy.CRGB(128,0,0),
  fancy.CRGB(255,0,0),
  fancy.CRGB(255,69,0),
 
  fancy.CRGB(220,20,60),
  fancy.CRGB(128,0,0),
  fancy.CRGB(255,0,0),
  fancy.CRGB (255,69,0),]

forest = [fancy.CRGB(0,100,0), #FastLED forest palette declaration
    fancy.CRGB(0,100,0),
    fancy.CRGB(85,107,47),
    fancy.CRGB(0,100,0),

    fancy.CRGB(0,128,0),
    fancy.CRGB(34,139,34),
    fancy.CRGB(107,142,35),
    fancy.CRGB(0,128,0),

    fancy.CRGB(46,139,87),
    fancy.CRGB(102,205,170),
    fancy.CRGB(50,205,50),
    fancy.CRGB(154,205,50),

    fancy.CRGB(144,238,144),
    fancy.CRGB(124,252,0),
    fancy.CRGB(102,205,170),
    fancy.CRGB(34,139,34)]

ocean = [fancy.CRGB(25,25,112), #FastLED ocean palette declaration
    fancy.CRGB(0,0,139),
    fancy.CRGB(25,25,112),
    fancy.CRGB(0,0,128),

    fancy.CRGB(0,0,139),
    fancy.CRGB(0,0,205),
    fancy.CRGB(46,139,87),
    fancy.CRGB(0,128,128),

    fancy.CRGB(95,158,160),
    fancy.CRGB(0,0,255),
    fancy.CRGB(0,139,139),
    fancy.CRGB(100,149,237),

    fancy.CRGB(127,255,212),
    fancy.CRGB(46,139,87),
    fancy.CRGB(0,255,255),
    fancy.CRGB(135,206,250)]
    
lava = [fancy.CRGB(0,0,0), #FastLED lava palette declaration
    fancy.CRGB(128,0,0),
    fancy.CRGB(0,0,0),
    fancy.CRGB(128,0,0),

    fancy.CRGB(139,0,0),
    fancy.CRGB(128,0,0),
    fancy.CRGB(139,0,0),

    fancy.CRGB(139,0,0),
    fancy.CRGB(139,0,0),
    fancy.CRGB(255,0,0),
    fancy.CRGB(255,165,0),

    fancy.CRGB(255,255,255),
    fancy.CRGB(255,165,0),
    fancy.CRGB(255,0,0),
    fancy.CRGB(139,0,0)]
    
cloud = [fancy.CRGB(0,0,255), #FastLED cloud palette declaration
    fancy.CRGB(0,0,139),
    fancy.CRGB(0,0,139),
    fancy.CRGB(0,0,139),
    
    fancy.CRGB(0,0,139),
    fancy.CRGB(0,0,139),
    fancy.CRGB(0,0,139),
    fancy.CRGB(0,0,139),

    fancy.CRGB(0,0,255),
    fancy.CRGB(0,0,139),
    fancy.CRGB(135,206,235),
    fancy.CRGB(135,206,235),

    fancy.CRGB(173,216,230),
    fancy.CRGB(255,255,255),
    fancy.CRGB(173,216,230),
    fancy.CRGB(135,206,235)]

party = [0x5500AB, 0x84007C, 0xB5004B, 0xE5001B,
         0xE81700, 0xB84700, 0xAB7700, 0xABAB00,
         0xAB5500, 0xDD2200, 0xF2000E, 0xC2003E,
         0x8F0071, 0x5F00A1, 0x2F00D0, 0x0007F9]

rainbow = [0xFF0000, 0xD52A00, 0xAB5500, 0xAB7F00,
           0xABAB00, 0x56D500, 0x00FF00, 0x00D52A,
           0x00AB55, 0x0056AA, 0x0000FF, 0x2A00D5,
           0x5500AB, 0x7F0081, 0xAB0055, 0xD5002B]

rainbow_stripe = [0xFF0000, 0x000000, 0xAB5500, 0x000000,
                  0xABAB00, 0x000000, 0x00FF00, 0x000000,
                  0x00AB55, 0x000000, 0x0000FF, 0x000000,
                  0x5500AB, 0x000000, 0xAB0055, 0x000000]

heat_colors = [0x330000, 0x660000, 0x990000, 0xCC0000, 0xFF0000,
               0xFF3300, 0xFF6600, 0xFF9900, 0xFFCC00, 0xFFFF00,
               0xFFFF33, 0xFFFF66, 0xFFFF99, 0xFFFFCC]


def wheel(pos):
    # Input a value 0 to 255 to get a color value.
    # The colours are a transition r - g - b - back to r.
    if (pos < 0) or (pos > 255):
        return (0, 0, 0)
    if pos < 85:
        return (int(pos * 3), int(255 - (pos * 3)), 0)
    elif pos < 170:
        pos -= 85
        return (int(255 - pos * 3), 0, int(pos * 3))
    else:
        pos -= 170
        return (0, int(pos * 3), int(255 - pos * 3))


def remapRange(value, leftMin, leftMax, rightMin, rightMax):
    # this remaps a value fromhere original (left) range to new (right) range
    # Figure out how 'wide' each range is
    leftSpan = leftMax - leftMin
    rightSpan = rightMax - rightMin

    # Convert the left range into a 0-1 range (int)
    valueScaled = int(value - leftMin) / int(leftSpan)

    # Convert the 0-1 range into a value in the right range.
    return int(rightMin + (valueScaled * rightSpan))


def keypress(color_palette):
    color_palette += 1

    if color_palette > 11:
        color_palette = 1

    return color_palette


while True:

    # check for button press
    currkeystate = button.value

    # button press, move to next pattern
    if (prevkeystate is not True) and currkeystate:
        ledmode = keypress(ledmode)

    # save button press state
    prevkeystate = currkeystate

    if ledmode == 1:palette = rainbow

    elif ledmode == 2:palette = rainbow_stripe
    
    elif ledmode == 3:palette = party

    elif ledmode == 4:palette = allRed

    elif ledmode == 5:palette = lava

    elif ledmode == 6:palette = sunset

    elif ledmode == 7:palette = allGold
        
    elif ledmode == 8:palette = forest
        
    elif ledmode == 9:palette = ocean

    elif ledmode == 10:palette = allPurple

    elif ledmode == 11:palette = galaxy


    for i in range(num_leds):
        color = fancy.palette_lookup(palette, offset + i / num_leds)
        color = fancy.gamma_adjust(color, brightness)
        strip[i] = color.pack()
    strip.show()

    if fadeup:
        offset += steps
        if offset >= 1:
            fadeup = False
    else:
        offset -= steps
        if offset <= 0:
            fadeup = True
 
