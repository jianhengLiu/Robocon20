#!/usr/bin/env python

# Copyright (c) 2011, Willow Garage, Inc.
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
#    * Redistributions of source code must retain the above copyright
#      notice, this list of conditions and the following disclaimer.
#    * Redistributions in binary form must reproduce the above copyright
#      notice, this list of conditions and the following disclaimer in the
#      documentation and/or other materials provided with the distribution.
#    * Neither the name of the Willow Garage, Inc. nor the names of its
#      contributors may be used to endorse or promote products derived from
#       this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.

import rospy
from geometry_msgs.msg import Twist
from geometry_msgs.msg import PoseStamped,Quaternion
import sys, select, termios, tty, numpy

from tf.transformations import quaternion_from_euler

msg = """
Control Your Car!
---------------------------
Moving around:
        x
   q    
   w   
   e
   r
   t 
space key, x : return the origin
CTRL-C to quit
"""

e = """
Communications Failed
"""


def getKey():
    tty.setraw(sys.stdin.fileno())
    rlist, _, _ = select.select([sys.stdin], [], [], 0.1)
    if rlist:
        key = sys.stdin.read(1)
    else:
        key = ''

    termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)
    return key


def position(x, y, angle):
    return "currently:\ttarget x: %s\ttarget vel y: %s\ttarget angle: %s " % (
        x, y, angle)


def pubPosition(x, y, angle):
    p = PoseStamped()
    p.header.frame_id = "map"
    p.header.stamp = rospy.Time.now()

    p.pose.position.x = x
    p.pose.position.y = y
    p.pose.position.z = 0

    q = quaternion_from_euler(0.0, 0.0, numpy.deg2rad(angle))
    p.pose.orientation = Quaternion(*q)

    pub.publish(p)
    print position(x, y, angle)


if __name__ == "__main__":
    settings = termios.tcgetattr(sys.stdin)

    rospy.init_node('keyboardSendPosition')
    pub = rospy.Publisher('move_base_simple/goal', PoseStamped, queue_size=1)

    status = 0
    x=0
    y=0
    angle=-90

    try:
        print msg
        while (1):
            key = getKey()
            if key == 'q':
                x=2.57
                y=-1
                status = status + 1
                pubPosition(x, y, angle)
            elif key == 'w':
                x=3.87
                y=-1
                status = status + 1
                pubPosition(x, y, angle)
            elif key == 'e':
                x=5.17
                y=-1
                status = status + 1
                pubPosition(x, y, angle)
            elif key == 'r':
                x=6.47
                y=-1
                status = status + 1
                pubPosition(x, y, angle)
            elif key == 't':
                x=7.77
                y=-1
                status = status + 1
                pubPosition(x, y, angle)
            elif key == ' ' or key == 'x':
                x=0.5
                y=0
                status = status + 1
                pubPosition(x, y, angle)
            elif key == ' ':
                x=0.5
                y=0
                status = status + 1
            else:
                if (key == '\x03'):
                    break

            if status == 20:
                print msg
                status = 0



    except:
        print e

    finally:
        print e

    termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)
