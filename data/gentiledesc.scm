#!/usr/bin/guile \
-e main -s
!#

(load "helper.scm")

(define (get-images-lst)
  (filter (lambda (filename)
	    (equal? (stat:type (stat (string-append "images/tiles/" filename))) 'regular))
	  (directory->list "images/tiles/")))

(define (extract-tiledesc filename)
  (list (string->symbol (string (string-ref filename 0)))
	(string->symbol (string (string-ref filename 1)))
	(string->symbol (string (string-ref filename 2)))
	(string->symbol (string (string-ref filename 3)))))

(define (filename-to-desc filename)
  (list (extract-tiledesc filename) 
	(string-append "tiles/" (substring filename 0 (- (string-length filename) 4)))))

(define (merge-entries lst)
  (let ((alst '()))
    (for-each (lambda (entry)
		(set! alst (assoc-set! alst (car entry) 
				       (cons (cadr entry)
					     (or (assoc-ref alst (car entry))
						 '())))))
	      lst)
    alst))

(define (main args)
  (println "(tiles ")
  (for-each (lambda (x) (write x)(newline))
	    (sort (merge-entries (map filename-to-desc (get-images-lst)))
		  (lambda (a b)
		    (string<=? (cadr a) (cadr b)))))
  (println ")"))

;; EOF ;;