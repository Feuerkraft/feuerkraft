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
  (display "### Sequence hook called")(newline))

(define my-vehicle9 (ai-vehicle-create 634 1063))

(ai-vehicle-drive-to my-vehicle9 546 1120)
(ai-vehicle-drive-to my-vehicle9 460 1165)
(ai-vehicle-drive-to my-vehicle9 432 1271)
(ai-vehicle-drive-to my-vehicle9 481 1374)
(ai-vehicle-drive-to my-vehicle9 575 1390)
(ai-vehicle-drive-to my-vehicle9 632 1385)
(ai-vehicle-drive-to my-vehicle9 676 1336)
(ai-vehicle-drive-to my-vehicle9 671 1221)

(sequence-add-hook (lambda () 
                     (effect-add-explosion 671 1221)
                     (object-remove my-vehicle9)))

(define (hello-world)
  (display "Hello World, I am a sequence hook")(newline))

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

(display "Vehicle id: ")(display my-vehicle1)(newline)

(for-each (lambda (pos)
            (ai-vehicle-drive-to my-vehicle1 (car pos) (cdr pos))
            (ai-vehicle-drive-to my-vehicle2 (car pos) (cdr pos))
            (ai-vehicle-drive-to my-vehicle3 (car pos) (cdr pos))
            (ai-vehicle-drive-to my-vehicle4 (car pos) (cdr pos))
            (ai-vehicle-drive-to my-vehicle5 (car pos) (cdr pos))
            (ai-vehicle-drive-to my-vehicle6 (car pos) (cdr pos)))
          path2)

(for-each (lambda (pos)
            (ai-vehicle-drive-to my-vehicle7 (car pos) (cdr pos)))
          path1)

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
            (1070 . 3745)))

(for-each (lambda (pos)
            (ai-vehicle-drive-to my-vehicle7 (car pos) (cdr pos)))
          '((1030 . 3701)
            (1030 . 3745)))

(for-each (lambda (pos)
            (ai-vehicle-drive-to my-vehicle8 (car pos) (cdr pos)))
          '((990 . 3701)
            (990 . 3745)))

;; EOF ;;