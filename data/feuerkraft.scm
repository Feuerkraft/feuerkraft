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
(define tank-type    6)
(define heli-type    7)
;; End: GameObj Types

;; Building Types
(define building:fuelstation (building-get-type-from-name "fuelstation"))
(define building:ammotent    (building-get-type-from-name "ammotent"))
(define building:wall        (building-get-type-from-name "wall"))
(define building:walldoor    (building-get-type-from-name "walldoor"))
(define building:tower       (building-get-type-from-name "tower"))
;; End: Building Types

(define (keywords2assoc lst)
  (cond ((and (pair? lst)
              (not (null? (cdr lst))))
         (let ((key   (car lst))
               (value (cadr lst)))
           (if (keyword? key)
               (cons (cons (keyword->symbol key) value)
                     (keywords2assoc (cddr lst))))))
        (else
         '())))

(define c:gameobj-create gameobj-create)
(define (gameobj-create type . lst)
  (c:gameobj-create type (keywords2assoc lst)))

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
  ;;(display "building-create-type: ")
  ;;(display name)
  ;;(display " -> ")
  ;;(display args)(newline)
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

(define (toggle-levelmap)
  (if (display-levelmap-visible)
      (display-hide-levelmap)
      (display-show-levelmap)))

(define (toggle-menu)
  (format #t "Menu Visible: ~a~%" (menu-visible))
  (if (menu-visible)
      (menu-hide)
      (menu-show 0)))

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

(define *satchels* '())
(menu-add-item comm-util-menu "Touch of Satchel"
               (lambda ()
                 (for-each (lambda (obj)
                             (satchel-detonate obj))
                           *satchels*)
                 (set! *satchels* '())))

(menu-add-item comm-util-menu "Drop Satchel"
               (lambda ()
                 (let* ((obj (gameobj-create satchel-type
                                             #:x-pos (gameobj-get-property (player-get-current-unit) "x-pos")
                                             #:y-pos (gameobj-get-property (player-get-current-unit) "y-pos"))))
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
                 (comm-unit-message (player-get-current-unit) "I need help!")

                 (let* ((obj (player-get-current-unit))
                        (target-x (+ (gameobj-get-property obj "x-pos") 100))
                        (target-y (+ (gameobj-get-property obj "y-pos") 100)))

                   (ai-goto 75 target-x target-y)
                   (ai-goto 76 target-x target-y)

                   (ai-vehicle-clear-orders wingman)
                   (ai-vehicle-drive-to wingman
                                        (inexact->exact target-x)
                                        (inexact->exact target-y))

                   (comm-unit-message 75 
                                      (format #f "On my way to ~a ~a"
                                              (inexact->exact target-x)
                                              (inexact->exact target-y))))))

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

;; End:   Interface definition

(define (random-ref vec)
  (vector-ref vec (random (vector-length vec))))

(define (gameobj-insert-func type . rest)
  (lambda (x y)
    (let ((obj (apply gameobj-create type
                      #:x-pos x
                      #:y-pos y
                      rest)))
      (ai-attach obj)
      obj)))


(define (building-insert-func type)
  (lambda (x y)
    (building-create (primitive-eval type)
                     (quotient (inexact->exact x) 40)
                     (quotient (inexact->exact y) 40))))

(define editor-insert-funcs (list 
                             (gameobj-insert-func tree-type)
                             (gameobj-insert-func marker-type)
                             (gameobj-insert-func mine-type)
                             (gameobj-insert-func satchel-type)
                             (gameobj-insert-func soldier-type)
                             (gameobj-insert-func tank-type)
                             (gameobj-insert-func tank-type 
                                                  #:turret "feuerkraft/turret2"
                                                  #:tank "feuerkraft/tank2")
                             (gameobj-insert-func heli-type)
                             (building-insert-func 'building:armored-generator)
                             (building-insert-func 'building:generator)
                             (building-insert-func 'building:garage)
                             (building-insert-func 'building:fuelstation)
                             (building-insert-func 'building:ammotent)
                             (building-insert-func 'building:walldoor)
                             (building-insert-func 'building:wall)
                             (building-insert-func 'building:tower)
                             ))
;; Make an endless list
(list-cdr-set! editor-insert-funcs (1- (length editor-insert-funcs)) editor-insert-funcs)

;; Core events
(input-register-callback "key_k" join-nearest-vehicle)

;; Support events, also reachable via menu
(input-register-callback "mouse_right"
                         (lambda ()
                           (let ((x (input-get-mouse-world-x))
                                 (y (input-get-mouse-world-y)))
                             (format #t "### Keyboard pressed: mouse: ~A ~A ~%" x y)
                             )))

(input-register-callback "key_f1" display-show-help)
(input-register-callback "key_f2" display-hide-help) 
(input-register-callback "key_m" toggle-levelmap)
(input-register-callback "key_escape" game-quit)
(input-register-callback "key_p"      game-pause)

(input-register-callback "mouse_left"
                         (lambda ()
                           (let ((x (input-get-mouse-world-x))
                                 (y (input-get-mouse-world-y)))
                              ((car editor-insert-funcs) x y))))

(input-register-callback "mouse_wheel_up"
                         (lambda ()
                           (set! editor-insert-funcs (cdr editor-insert-funcs))))

(input-register-callback "mouse_wheel_down"
                         (lambda ()
                           (set! editor-insert-funcs (cdr editor-insert-funcs))))

;; EOF ;;