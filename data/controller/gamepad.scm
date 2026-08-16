;; Feuerkraft controller config using SDL_GameController indices.
;;
;; Axes:  0=LEFTX 1=LEFTY 2=RIGHTX 3=RIGHTY 4=TRIGGERLEFT 5=TRIGGERRIGHT
;; Buttons: 0=A 1=B 2=X 3=Y 4=BACK 5=GUIDE 6=START
;;          7=LEFTSTICK 8=RIGHTSTICK 9=LEFTSHOULDER 10=RIGHTSHOULDER
;;          11=DPAD_UP 12=DPAD_DOWN 13=DPAD_LEFT 14=DPAD_RIGHT
;;
;; (joystick-button device button) / (joystick-axis device axis)
;; device is the GameController index (usually 0 for the first pad).

(feuerkraft-controller

 (primary-button   (multi-button
                    (joystick-button 0 9)   ;; LEFTSHOULDER
                    (joystick-button 0 0))) ;; A
 (secondary-button (joystick-button 0 8))  ;; RIGHTSTICK / was raw 8
 (use-button       (joystick-button 0 3))  ;; Y
 (menu-button      (joystick-button 0 2))  ;; X

 (orientation-axis (joystick-axis 0 0))    ;; LEFTX
 (accelerate-axis  (joystick-axis 0 1))    ;; LEFTY
 (strafe-axis      (joystick-axis 0 2)))   ;; RIGHTX

;; EOF ;;
