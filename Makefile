all: pdf

pdf: fz.tex
	astyle *.cpp -r -A1 --indent=spaces=4
	xelatex fz.tex
	xelatex fz.tex

clean:
	rm -f *.aux *.log *.out *.toc *.pdf
