(load "pathdata.scm")

;;(load-extension "/home/ingo/projects/feuerkraft/cvs/src/scripting/.libs/libguile-feuerkraft.so" 
;;                "SWIG_init")

(define my-vehicle1 (ai-vehicle-create 233 1759))
(define my-vehicle2 (ai-vehicle-create 233 1859))
(define my-vehicle3 (ai-vehicle-create 233 1959))
(define my-vehicle4 (ai-vehicle-create 233 2059))
(define my-vehicle5 (ai-vehicle-create 233 2159))
(define my-vehicle6 (ai-vehicle-create 233 2259))

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
     (trigger-add-timed (+ 1 (/ x 200.0))
                        (lambda ()
                          (effect-add-explosion (+ 0 (+ x (- (random 300) 150)))
                                                (+ 200 (random 400))))))))

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
  (ai-vehicle-wait my-vehicle1 1)
  (ai-vehicle-wait my-vehicle2 2)
  (ai-vehicle-wait my-vehicle3 3)
  (ai-vehicle-wait my-vehicle4 4)
  (ai-vehicle-wait my-vehicle5 5)
  (ai-vehicle-wait my-vehicle6 6)

  (for-each (lambda (pos)
              (ai-vehicle-drive-to my-vehicle1 (car pos) (cdr pos))
              (ai-vehicle-drive-to my-vehicle2 (car pos) (cdr pos))
              (ai-vehicle-drive-to my-vehicle3 (car pos) (cdr pos))
              (ai-vehicle-drive-to my-vehicle4 (car pos) (cdr pos))
              (ai-vehicle-drive-to my-vehicle5 (car pos) (cdr pos))
              (ai-vehicle-drive-to my-vehicle6 (car pos) (cdr pos)))
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
              (ai-vehicle-drive-to my-vehicle1 (car pos) (cdr pos))
              (ai-vehicle-drive-to my-vehicle2 (car pos) (cdr pos))
              (ai-vehicle-drive-to my-vehicle3 (car pos) (cdr pos))
              (ai-vehicle-drive-to my-vehicle4 (car pos) (cdr pos))
              (ai-vehicle-drive-to my-vehicle5 (car pos) (cdr pos))
              (ai-vehicle-drive-to my-vehicle6 (car pos) (cdr pos)))
            path2)

  (sequence-add-hook (lambda ()
                       (trigger-add-timed 5 convoy-reverse)))

  (for-each (lambda (pos)
              (ai-vehicle-drive-to my-vehicle1 (car pos) (cdr pos)))
            '((1270 . 3701)
              (1270 . 3745)))

  (for-each (lambda (pos)
              (ai-vehicle-drive-to my-vehicle2 (car pos) (cdr pos)))
            '((1230 . 3701)
              (1230 . 3745)))

  (for-each (lambda (pos)
              (ai-vehicle-drive-to my-vehicle3 (car pos) (cdr pos)))
            '((1190 . 3701)
              (1190 . 3745)))

  (for-each (lambda (pos)
              (ai-vehicle-drive-to my-vehicle4 (car pos) (cdr pos)))
            '((1150 . 3701)
              (1150 . 3745)))

  (for-each (lambda (pos)
              (ai-vehicle-drive-to my-vehicle5 (car pos) (cdr pos)))
            '((1110 . 3701)
              (1110 . 3745)))

  (for-each (lambda (pos)
              (ai-vehicle-drive-to my-vehicle6 (car pos) (cdr pos)))
            '((1070 . 3701)
              (1070 . 3745))))

;; EOF ;;