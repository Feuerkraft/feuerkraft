;; This file contains a bunch of overrides of exported functions to
;; make there handling easier on the scheme side, the C version is
;; still accessible via the 'c:' prefix.

;; GameObj Types
;; see: game_obj_factory.cxx
(define tree-type    1)
(define marker-type  2)
(define mine-type    3)
(define satchel-type 4)
(define soldier-type 5)
;; End: GameObj Types

(define (gameobj-get-type obj)
  "return the type of a unit"
  (cond ((gameobj-is-helicopter obj)
         'helicopter)
        ((gameobj-is-soldier obj)
         'soldier)
        ((gameobj-is-vehicle obj)
         'vehicle)
        ((gameobj-is-unit obj)
         'unit)
        (else
         'unknown)))

(define (display-units type)
  "Display all units and there type in a human readable way"
  (display ">>> Start: Game Units <<<\n")
  (for-each (lambda (obj)
              (cond ((gameobj-is-unit obj)
                     (cond ((or (equal? (gameobj-get-type obj) type)
                                (equal? type 'all))
                            (format #t "[~a]~%" (gameobj-get-type obj))
                            (for-each (lambda (prop)
                                        (format #t 
                                                "  ~a = ~a~%"
                                                prop
                                                (gameobj-get-property obj prop)))
                                      (gameobj-properties obj))
                            (newline))))))
            (gameobj-get-all))
  (display ">>> End: Game Units <<<\n"))

(define *static-binary* #t)

;;(cond ((not *static-binary*)
;;       (use-modules (ice-9 readline))
;;       (activate-readline)))

(display "### Loading helper function...")(newline)

(define c:comm-send-message comm-send-message)
(define c:building-create-type building-create-type)

(define (comm-send-message color . msg)
  (c:comm-send-message 0 ;; FIXME: color 'node
                       (call-with-output-string 
                        (lambda (port)
                          (for-each (lambda (el)
                                      (display el port))
                                    msg)))))

(define (building-create-type name . args)
  (display "building-create-type: ")
  (display name)
  (display " -> ")
  (display args)(newline)
  (c:building-create-type name args))

(define (feuerkraft:repl)
  (display "### Feuerkraft repl, exit with (quit)\n")
  (let ((old-prompt scm-repl-prompt))
    (set-repl-prompt! "feuerkraft> ")
    (catch #t
           (lambda ()
             (top-repl)
             (display "Feuerkraft Readline exited nicly.\n"))
           (lambda args 
             (display "Error: ")
             (display args)(newline)))
    (set-repl-prompt! old-prompt)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Game Play related stuff ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (join-nearest-vehicle)
  (let ((obj (player-get-current-unit)))
    (cond ((gameobj-is-soldier obj)
           (let ((vehicle (vehicle-find-nearest 
                           (gameobj-get-property obj "x-pos")
                           (gameobj-get-property obj "y-pos")
                           50)))
             (cond ((not (= vehicle 0))
                    ;;(format #t "Found Vehicle: ~a~%" vehicle)
                    (player-set-current-unit vehicle)
                    (gameobj-set-property obj "hidden" #t)
                    (comm-send-message 'note "You entered vehicle " vehicle))
                   (else
                    (comm-send-message 'note "No vehicle around to enter")))
             ))
          (else
           (comm-send-message 'note "You left vehicle " obj)

           (let* ((orientation (- (gameobj-get-property obj "orientation") (/ 3.1415927 2.0)))
                  (x (* (cos orientation) 25))
                  (y (* (sin orientation) 25)))
             
             (gameobj-set-property (player-get-soldier)
                                   "x-pos" (+ (gameobj-get-property obj "x-pos") x))
             (gameobj-set-property (player-get-soldier)
                                   "y-pos" (+ (gameobj-get-property obj "y-pos") y))
             (gameobj-set-property (player-get-soldier)
                                   "orientation" (+ (gameobj-get-property obj "orientation")
                                                    (/ 3.1415927 2.0)))

             (player-set-current-unit (player-get-soldier))
             (gameobj-set-property (player-get-soldier) "hidden" #f))))))

(input-register-callback "key_k" join-nearest-vehicle)

(input-register-callback "key_f1" display-show-help)
(input-register-callback "key_f2" display-hide-help)

(input-register-callback "key_m" (lambda ()
                                   (if (display-levelmap-visible)
                                       (display-hide-levelmap)
                                       (display-show-levelmap))))

(input-register-callback "key_a" (lambda () 
                                   (format #t "Menu Visible: ~a~%" (menu-visible))
                                   (if (menu-visible)
                                       (menu-hide)
                                       (menu-show 0))))

(input-register-callback "key_escape" game-quit)
(input-register-callback "key_p"      game-pause)

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
                 (gameobj-create mine-type `((x-pos ,(gameobj-get-property (player-get-current-unit) "x-pos"))
                                             (y-pos ,(gameobj-get-property (player-get-current-unit) "y-pos"))))))

(define *satchels* '())
(menu-add-item comm-util-menu "Touch of Satchel"
               (lambda ()
                 (for-each (lambda (obj)
                             (satchel-detonate obj))
                           *satchels*)
                 (set! *satchels* '())))

(menu-add-item comm-util-menu "Drop Satchel" 
               (lambda ()
                 (let* ((obj (gameobj-create
                              satchel-type `((x-pos ,(gameobj-get-property (player-get-current-unit) "x-pos"))
                                             (y-pos ,(gameobj-get-property (player-get-current-unit) "y-pos"))))))
                   (format #t "Put Satchel: ~a~%" obj)
                   (set! *satchels* (cons obj *satchels*)))))


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
                   
                   (ai-goto 75 target-x target-y)
                   (ai-goto 76 target-x target-y)

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
                 (comm-send-message 'player "Request Bomber support!")
                 (let ((obj (player-get-current-unit)))
                   (bomber-attack (inexact->exact (gameobj-get-property obj "x-pos"))
                                  (inexact->exact (gameobj-get-property obj "y-pos"))))))

(menu-add-item comm-menu "Start/Land Heli"
               (lambda ()
                 (helicopter-start-or-land (player-get-current-unit))))

(menu-add-item comm-menu "Mount Vehicle" join-nearest-vehicle)

;;(menu-add-item comm-menu "Back >>>" menu-hide)

;; End:   Interface definition

(input-register-callback "mouse_right" 
                         (lambda ()
                           (let ((x (input-get-mouse-world-x))
                                 (y (input-get-mouse-world-y)))
                             (format #t "### Keyboard pressed: mouse: ~A ~A ~%" x y)
                             )))


(define editor-type-list (list tree-type
                               marker-type
                               mine-type
                               satchel-type
                               soldier-type))
(list-cdr-set! editor-type-list (1- (length editor-type-list)) editor-type-list)

(input-register-callback "mouse_left" 
                         (lambda ()
                           (let ((x (input-get-mouse-world-x))
                                 (y (input-get-mouse-world-y)))
                             
                             (let ((obj (gameobj-create (car editor-type-list)
                                                        `((x-pos ,x)
                                                          (y-pos ,y)))))
                               (ai-attach obj)))))
  
(input-register-callback "mouse_wheel_up" 
                         (lambda ()
                           (set! editor-type-list (cdr editor-type-list))
                           (display "Wheel UP\n")))

(input-register-callback "mouse_wheel_down" 
                         (lambda ()
                           (set! editor-type-list (cdr editor-type-list))
                           (display "Wheel UP\n")))

;; EOF ;;