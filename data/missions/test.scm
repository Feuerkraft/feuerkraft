(display "============== SCRIPT START ======================\n")

;;(load-extension "/home/ingo/projects/feuerkraft/cvs/src/scripting/.libs/libguile-feuerkraft.so" 
;;                "SWIG_init")

(define building:house1
  (building-create-type #:sprite "feuerkraft/house1"
                        #:width  3
                        #:height 3))

(define building:garage
  (building-create-type #:sprite "feuerkraft/garage"
                        #:width  3
                        #:height 4))

(define building:house2
  (building-create-type #:sprite "feuerkraft/house2"
                        #:width  3
                        #:height 3))

(define building:generator
  (building-create-type #:sprite "feuerkraft/generator"
                        #:width  3
                        #:height 2))

(define building:armored-generator
  (building-create-type #:sprite "feuerkraft/armoredgenerator"
                        #:width  3
                        #:height 3))

(building-create building:house1 10 35)
(building-create building:house2 14 35)

(building-create building:garage 13 43)
(building-create building:garage 16 43)
(building-create building:garage 19 43)
(building-create building:garage 22 43)

(building-create building:armored-generator 25 43)

(building-create building:garage 13 49)
(building-create building:garage 16 49)
(building-create building:garage 19 49)
(building-create building:garage 22 49)

(building-create building:armored-generator 25 49)

(building-create building:generator 10 38)
(building-create building:armored-generator 5 38)

(display "MYBUILDING TYPE: ")(display building:house1)(newline)

(building-create 1 4 32)
(building-create 1 4 33)
(building-create 1 4 34)

(define my-vehicle1 (ai-vehicle-create 233 1400))
(define my-vehicle2 (ai-vehicle-create 233 2000))

(define vehicle-group (list my-vehicle1 my-vehicle2))

(define my-vehicle7 (ai-vehicle-create 1628 1060))
(define my-vehicle8 (ai-vehicle-create 634 1063))

(define (seqhook)
  (comm-send-message 0 "Sequence hook called"))

(define my-vehicle9 (ai-vehicle-create 634 1063))

(trigger-add-tile 
 14 6  
 (lambda (id)
   (comm-send-message 0 "### Bomber attack detected")
   (do ((x 0 (+ x 20)))
       ((not (< x 1000)))
     (trigger-add-timed (+ 5 (/ x 200.0))
                        (lambda ()
                          (effect-add-explosion (+ 0 (+ x (- (random 300) 150)))
                                                (+ 200 (random 400)))))
     (if (= (random 3) 1)
         (trigger-add-timed (/ x 200.0)
                            (lambda () (sound-play-sound "bomb"))))
     )))

(ai-vehicle-drive-to my-vehicle9 546 1120)
(ai-vehicle-drive-to my-vehicle9 460 1165)
(ai-vehicle-drive-to my-vehicle9 432 1271)
(ai-vehicle-drive-to my-vehicle9 481 1374)
(ai-vehicle-drive-to my-vehicle9 575 1390)
(ai-vehicle-drive-to my-vehicle9 632 1385)
(ai-vehicle-drive-to my-vehicle9 676 1336)
(ai-vehicle-drive-to my-vehicle9 671 1221)
(ai-vehicle-wait     my-vehicle9 3)


(let ((func (lambda (id)
              (comm-send-message 0 "Explosion: " id)
              (effect-add-explosion 546 1120))))
  (trigger-add-tile 13 29 func)
  (trigger-add-tile 14 29 func)
  (trigger-add-tile 13 28 func)
  (trigger-add-tile 14 28 func))

(trigger-add-tile 5 41 (lambda (id) (convoy-start)))

(sequence-add-hook (lambda () 
                     (effect-add-explosion 671 1221)
                     (object-remove my-vehicle9)))

(define (hello-world)
  (comm-send-message 0 "Hello World, I am a sequence hook"))

(let ((id (sequence-start)))
  (sequence-add-hook hello-world)
  (sequence-end id))

(ai-vehicle-wait my-vehicle8 3)
(for-each (lambda (pos)
            (ai-vehicle-drive-to my-vehicle8 (car pos) (cdr pos)))
          path3)
(ai-vehicle-wait my-vehicle8 3.5)
(for-each (lambda (pos)
            (ai-vehicle-drive-to my-vehicle8 (car pos) (cdr pos)))
          path4)

(comm-send-message 0 "Vehicle id: " my-vehicle1)

(define (convoy-reverse)
  (for-each (lambda (pos)
              (for-each (lambda (vehicle)
                          (ai-vehicle-drive-to vehicle (car pos) (cdr pos)))
                        vehicle-group))
            (reverse path2)))

(for-each (lambda (pos)
            (ai-vehicle-drive-to my-vehicle7 (car pos) (cdr pos)))
          path1)

(for-each (lambda (pos)
            (ai-vehicle-drive-to my-vehicle7 (car pos) (cdr pos)))
          '((1030 . 3701)
            (1030 . 3745)))

(for-each (lambda (pos)
            (ai-vehicle-drive-to my-vehicle8 (car pos) (cdr pos)))
          '((990 . 3701)
            (990 . 3745)))

(define (convoy-start)
  (for-each (lambda (pos)
              (for-each (lambda (vehicle)
                          (ai-vehicle-drive-to vehicle (car pos) (cdr pos)))
                        vehicle-group))
            path2)

  (sequence-add-hook (lambda ()
                       (trigger-add-timed 5 convoy-reverse))))

(display "================ SCRIPT STOP ======================\n")

;; EOF ;;