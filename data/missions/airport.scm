(define building:house1
  (building-create-type "house1"
                        #:sprite "feuerkraft/house1"
                        #:width  3
                        #:height 3))

(define building:garage
  (building-create-type "garage"
                        #:sprite "feuerkraft/garage"
                        #:width  3
                        #:height 4))

(define building:house2
  (building-create-type "house2"
                        #:sprite "feuerkraft/house2"
                        #:width  3
                        #:height 3))

(define building:generator
  (building-create-type "generator"
                        #:sprite "feuerkraft/generator"
                        #:width  3
                        #:height 2))

(define building:armored-generator
  (building-create-type "armored-generator"
                        #:sprite "feuerkraft/armoredgenerator"
                        #:width  3
                        #:height 3))

(define building:parking-lot
  (building-create-type "parking-lot"
                        #:sprite "feuerkraft/start"
                        #:width  0
                        #:height 0))

(do ((x 0 (+ x 64)))
    ((> x 500))
  (do ((y 0 (+ y 64)))
      ((> y 500))
    (gameobj-create mine-type 
                    #:x-pos (+ 500.0 x)
                    #:y-pos (+ 2200.0 y))))

(gameobj-create tree-type 
                #:x-pos 10.0
                #:y-pos 10.0
                #:sprite "feuerkraft/start")

(gameobj-create tree-type 
                #:x-pos 1.0
                #:y-pos 315.0
                #:sprite "feuerkraft/start")

(gameobj-create tree-type
                #:x-pos 59.0
                #:y-pos 465.0
                #:sprite "feuerkraft/start")

(gameobj-create tree-type 
                #:x-pos -230.0
                #:y-pos  397.0
                #:sprite "feuerkraft/start")

(gameobj-create tree-type
                #:x-pos -250.0
                #:y-pos 13.0
                #:sprite "feuerkraft/start")

(building-create building:parking-lot 8  33)
(building-create building:parking-lot 11 33)
(building-create building:parking-lot 14 33)

(define (switch-to-tank1 id)
  (player-set-current-unit 7))

(define (switch-to-tank2 id)
  (player-set-current-unit 8))

(define (switch-to-heli id)
  (player-set-current-unit 6))

(define (switch-to-jeep id)
  (player-set-current-unit 5))

(trigger-add-tile  8 33 switch-to-jeep)
(trigger-add-tile 11 33 switch-to-tank2)
(trigger-add-tile 14 33 switch-to-heli)

(building-create building:house1 10 35)
(building-create building:house2 14 35)

(building-create building:garage 13 43)
(building-create building:garage 16 43)
(building-create building:garage 19 43)
(building-create building:garage 22 43)

(building-create building:garage 13 49)
(building-create building:garage 16 49)
(building-create building:garage 19 49)
(building-create building:garage 22 49)

(building-create building:armored-generator 25 49)

(building-create building:generator 10 38)
(building-create building:armored-generator 5 38)

(define path-to-base
  '((4584 . 460) (4080 . 460) (3575 . 462) (3029 . 455) (2538 . 468)
    (2143 . 458) (1798 . 458) (1520 . 454) (1421 . 571) (1425 . 858)
    (1419 . 1101) (1308 . 1182) (1014 . 1178) (819 . 1180) (741 . 1245)
    (739 . 1417)    (742 . 1619)    (835 . 1662)    (1400 . 1659)
    (1921 . 1664)    (2401 . 1660)    (2501 . 1707)    (2559 . 1763)
    (2685 . 1681)    (2573 . 1579)    (2515 . 1652)    (2239 . 1661)
    (1696 . 1666)    (1262 . 1653)    (973 . 1659)    (650 . 1665)
    (512 . 1661)    (459 . 1713)
    (467 . 2124) (466 . 2426) (469 . 2798) (464 . 3063) (460 . 3540) 
    (463 . 3837) (463 . 4109) (459 . 4355) (466 . 4682) (463 . 4774)
    (544 . 4856) (740 . 4860) (819 . 4971) (824 . 5326) (821 . 5637)
    (823 . 5946)  (826 . 6222)  (830 . 6462)  (935 . 6503) (1223 . 6504)
    (1566 . 6496) (1839 . 6504) (1785 . 6657) (1471 . 6973) (1509 . 7076)
    (1761 . 7329) (2075 . 7633) (2342 . 7903) (2486 . 8049) (2752 . 8056)
    (3153 . 8064) (3424 . 8051) (3953 . 8062) (4310 . 8061) (4582 . 8062)
    (4904 . 8064) (5107 . 7891) (5382 . 7613) (5620 . 7379) (5921 . 7099)
    (6223 . 6770) (6312 . 6739) (6342 . 6528) (6338 . 6380) (6241 . 6338)
    (5808 . 6338) (5721 . 6338) (5607 . 6249) (5503 . 6146) (5504 . 6020)
    (5499 . 5760) (5500 . 5574) (5491 . 5395) (5500 . 5261) (5628 . 5217)
    (5897 . 5211) (6221 . 5217) (6524 . 5220) (6774 . 5219) (7014 . 5216)
    (7219 . 5220) (7325 . 5328) (7476 . 5486) (7651 . 5647) (7837 . 5840)
    (8019 . 6013) (8325 . 6021) (8709 . 6024) (9054 . 6016) (9140 . 6018)
    (9185 . 5886) (9180 . 5616) (9272 . 5541) (9511 . 5545) (9941 . 5534)
    (10012 . 5615) (10018 . 5779) (9918 . 5821) (9761 . 5819) 
    (9635 . 5814) (9587 . 5765)))

(define ai-vehicle (ai-vehicle-create (caar path-to-base) (cdar path-to-base)))
(define wingman ai-vehicle)

(define (vehicles-start)
  (for-each (lambda (pos)
              (ai-vehicle-drive-to ai-vehicle (car pos) (cdr pos)))
            path-to-base))

(vehicles-start)

(input-register-callback "key_a"
                         (lambda ()
                           (display "### Keyboard pressed: a")
                           (newline)
                           (if (= (player-get-current-unit) 6)
                               (player-set-current-unit 8)
                               (player-set-current-unit 6))))

                                        ;(gameobj-create 2 '#:x-pos 470.0)
                                        ;                    (y-pos 1134.0)))

(define (bomber-attack x-pos y-pos)
  (trigger-add-timed 
   3
   (lambda ()
     (comm-send-message 'base "Roger that. Bomber attack will start in 5 seconds.")
     (comm-send-message 'base "Move away there now!")

     (trigger-add-timed 
      5
      (lambda ()
        (comm-send-message 'bomber "Bombs away!")
        (do ((x 0 (+ x 20)))
            ((not (< x 1000)))
          (trigger-add-timed (+ 5 (/ x 200.0))
                             (lambda ()
                               (effect-add-explosion (+ x-pos -500 (+ x (- (random 300) 150)))
                                                     (+ y-pos -200 (random 400)))))
          (if (= (random 3) 1)
              (trigger-add-timed (/ x 200.0)
                                 (lambda () (sound-play-sound "bomb"))))
          ))))))

;; Begin: Interface definition
(define comm-menu         (menu-create))
(define comm-util-menu    (menu-create))
(define comm-debug-menu   (menu-create))
(define comm-retreat-menu (menu-create))
(define comm-attack-menu  (menu-create))

;;;;;;;;;;;;;;;;
;; Debug Menu ;;
;;;;;;;;;;;;;;;;
(menu-add-submenu-item comm-menu "Debug" comm-debug-menu)

(menu-add-item comm-debug-menu "Load 'test.feu'"
               (lambda ()
                 (game-load "missions/test.feu")))
(menu-add-item comm-debug-menu "Load 'airport.feu'"
               (lambda ()
                 (game-load "missions/airport.feu")))

(menu-add-item comm-debug-menu "Toggle Colmap"
               (lambda ()
                 (debug-set-flag "colmap" (not (debug-get-flag "colmap")))))

(menu-add-item comm-debug-menu "Pause" (lambda () (game-pause)))
(menu-add-item comm-debug-menu "Quit" (lambda () (game-quit)))

;;;;;;;;;;;;;;;
;; Util Menu ;;
;;;;;;;;;;;;;;;
(menu-add-submenu-item comm-menu "Utilities" comm-util-menu)

(menu-add-item comm-util-menu "Drop Mine" 
               (lambda ()
                 (gameobj-create mine-type
                                 #:x-pos (gameobj-get-property (player-get-current-unit) "x-pos")
                                 #:y-pos (gameobj-get-property (player-get-current-unit) "y-pos"))))

(menu-add-item comm-util-menu "Show Levelmap" 
               (lambda ()
                 (if (display-levelmap-visible)
                     (display-hide-levelmap)
                     (display-show-levelmap))))

;;;;;;;;;;;;;;;;;;
;; Retreat Menu ;;
;;;;;;;;;;;;;;;;;;
(menu-add-submenu-item comm-menu "Retreat" comm-retreat-menu)

(menu-add-item comm-retreat-menu "Back to base" 
               (lambda ()
                 (comm-send-message 'player "Everybody return to base!")))

(menu-add-item comm-retreat-menu "Join at my pos" 
               (lambda ()
                 (comm-send-message 'player "Everybody join at my pos!")))

;;(menu-add-submenu-item comm-retreat-menu "Back" comm-menu)

;;;;;;;;;;;;;;;;;
;; Attack Menu ;;
;;;;;;;;;;;;;;;;;
(menu-add-submenu-item comm-menu "Attack" comm-attack-menu)

(menu-add-item comm-attack-menu "Attack Tank"
               (lambda () 
                 (comm-send-message 'player "Attack Tank at 2 o'clock")))

(menu-add-item comm-attack-menu "Fire at Will"
               (lambda () 
                 (comm-send-message 'player "Everybody fire at Will!")))

;;(menu-add-submenu-item comm-attack-menu "Back" comm-menu)

;;;;;;;;;;;;;;;;;
;; Other Stuff ;;
;;;;;;;;;;;;;;;;;
(menu-add-item comm-menu "Help!" 
               (lambda () 
                 (comm-send-message 'player "I need help!")

                 (let* ((obj (player-get-current-unit))
                        (target-x (+ (gameobj-get-property obj "x-pos") 100))
                        (target-y (+ (gameobj-get-property obj "y-pos") 100)))
                   
                   (ai-vehicle-clear-orders wingman)
                   (ai-vehicle-drive-to wingman 
                                        (inexact->exact target-x)
                                        (inexact->exact target-y))

                   (comm-send-message 'wingman "On my way to " 
                                      (inexact->exact target-x)
                                      " "
                                      (inexact->exact target-y)))))

(menu-add-item comm-menu "Bomb Attack!" 
               (lambda () 
                 (comm-unit-message (player-get-current-unit) "Request Bomber support!")
                 (let ((obj (player-get-current-unit)))
                   (bomber-attack (inexact->exact (gameobj-get-property obj "x-pos"))
                                  (inexact->exact (gameobj-get-property obj "y-pos"))))))

(menu-add-item comm-menu "Start/Land Heli"
               (lambda ()
                 (helicopter-start-or-land (player-get-current-unit))))

(menu-add-item comm-menu "Mount Vehicle" join-nearest-vehicle)

;;(menu-add-item comm-menu "Back >>>" menu-hide)

;; End:   Interface definition

;;(define soldier1 (player-get-soldier))
(define soldier2 (gameobj-create soldier-type 
                                 #:x-pos 500.0
                                 #:y-pos 200.0))

(define soldier3 (gameobj-create soldier-type 
                                 #:x-pos 500.0
                                 #:y-pos 200.0))

(input-register-callback "key_2" (lambda () (player-set-soldier soldier2)))
(input-register-callback "key_3" (lambda () (player-set-soldier soldier3)))

(define (airport:add-trigger x y proc)
  (let ((obj (gameobj-create marker-type
                             #:x-pos (- (* (1+ x) 40) 20)
                             #:y-pos (- (* (1+ y) 40) 20))))

    (trigger-add-tile x y (lambda (object) 
                            (gameobj-remove obj)
                            (proc)))))

(define *waypoints* '((15 . 30)
                      (17 . 30)
                      (19 . 30)
                      (21 . 30)
                      (23 . 30)
                      (25 . 30)))

(define (airport:add-waypoints lst)
  (cond ((not (null? lst))
         (airport:add-trigger (caar lst) (cdar lst) 
                              (lambda ()
                                (airport:add-waypoints (cdr lst))
                                )))
        (else
         (comm-send-message 'player "Mission successfull"))))

(airport:add-waypoints *waypoints*)

(input-register-callback "key_4"
                         (lambda ()
                           (comm-unit-message 82 "Heavy damage taken\nNeed help emidiatly!")))

;; EOF ;;
