SORT	START	0
		J		INPUT
EINPUT	J		SELECT
ESORT	END		SORT
	
INPUT	RD		STDIN				// 5개의 숫자 입력
		COMP	SEP
		JEQ		TSAVE
		COMP	ETR
		JEQ		ERROR
		COMP	#69
		JEQ		CEND
		J		CHECK
ECHECK	JSUB	CKBYTE
		SUB		#48
		ADD		TEMP
		MUL		#10
		STA		TEMP
		CLEAR	A
		J		INPUT

CHECK	LDT		NUMFIR
		COMPR	A,T
		JLT		ERROR
		LDT		NUMEND
		COMPR	A,T
		JGT		ERROR
		CLEAR	T
		J		ECHECK	

TSAVE	LDA		TEMP				// 수 저장
		DIV		#10
		STA		ARY,X
		LDA		WRD
		ADDR	A,X
		LDA		IXB
		ADD		#1
		COMP	#9
		JEQ		ERROR
		STA		IXB
		CLEAR	A
		STA		IXA
		STA		TEMP
		J		INPUT

CKBYTE	RMO		A,S					// 각 수의 자리 확인
		CLEAR	A
		LDA		IXA
		COMP	#5
		JEQ		ERROR
		ADD		#1
		STA		IXA
		CLEAR	A
		RMO		S,A
		CLEAR	S
		RSUB

CEND	LDX		#0
		LDS		IXB
		COMPR	X,S
		JEQ		ERROR
		RMO		A,B
		LDCH	EOF,X
		COMPR	A,B
		JEQ		OKONE
		J		ERROR
OKONE	STCH	BUFFER,X
SLOOP	LDA		#1		
		ADDR	A,X
		CLEAR	A
		RD		STDIN
		COMP	ETR
		JEQ		EINPUT
		RMO		A,B
		LDCH	EOF,X
		COMPR	A,B
		JEQ		OKTWO
		J		ERROR
OKTWO	STCH	BUFFER,X
		J		SLOOP

STATE	CLEAR	X						// 출력
STLOOP	LDA		ARY,X
		J		PRINTS
STLOOT	LDA		#3
		ADDR	A,X
		RMO		X,A
		DIV		#3
		COMP	IXB
		JEQ		PRINTE
		J		PRINTB
STLOOJ	J		STLOOP

PRINTS	RMO		A,T
		STX		IXC
		LDA		#1
		CLEAR	X
		ADDR	A,X
		CLEAR	A
		CLEAR	B
		ADDR	T,A
		COMP	#10
		JLT		PRINTO
PLOOP	DIV		#10
PLOOPN	STA		IXA
		LDA		#0
		ADDR	T,A
		COMP	#0
		JEQ		BEOUT
		LDA		IXA
		COMP	#10
		JLT		PLOOT
		STA		IXA
		LDA		#1
		ADDR	A,X
		LDA		IXA
		J		PLOOP
PLOOT	J		PRINT	
PLOOTN	COMPR	X,B
		JEQ		PLOOTH
		MUL		#10
		STA		IXA
		LDA		#1
		ADDR	A,B
		LDA		IXA
		J		PLOOTN
PLOOTH	SUBR	A,T
		LDA		#0
		ADDR	T,A
		CLEAR	X
		CLEAR	B
		J		PLOOPN

BEOUT	LDX		IXC
		CLEAR	B
		CLEAR	T
		J		STLOOT

PRINT	ADD		#48
		TD		STDOUT				// 출력만 담당
		JEQ		PRINT
		WD		STDOUT
		SUB		#48
		J		PLOOTN

PRINTO	ADD		#48
		TD		STDOUT
		JEQ		PRINTO
		WD		STDOUT
		CLEAR	A
		LDX		IXC
		J		STLOOT

PRINTB	STA		IXA
		LDA		SEP
		TD		STDOUT				// 공백 출력
		JEQ		PRINTB
		WD		STDOUT
		LDA		IXA
		J		STLOOJ

PRINTE	LDA		#14
		TD		STDOUT
		JEQ		PRINTE
		WD		STDOUT
		LDA		#10
PRINTET	TD		STDOUT
		JEQ		PRINTET
		WD		STDOUT		
		RSUB

SELECT	CLEAR	A
		CLEAR	X
		CLEAR	S					// Current Index
		CLEAR	T					// Smallest Value
		CLEAR	B					// Pivot Index
		LDT		ARY,X				// IXD는 최소 값의 인덱스
		STT		IXE
		LDA		#1					// IXE는 Pivot Value
		ADDR	A,S
SELF	LDA		IXB
		COMPR	A,B
		JEQ		RET
SELM	COMPR	A,S
		JEQ		SWAP
		RMO		S,A
		MUL		#3
		RMO		A,X
		LDA		ARY,X
		COMPR	A,T					// Smallest Comparison
		JLT		SELT
SELMT	LDA		#1
		ADDR	A,S
		LDA		IXB
		J		SELM

SELT	RMO		A,T
		STS		IXD
		J		SELMT
			
SWAP	LDA		IXD
		MUL		#3
		RMO		A,X
		LDA		IXE
		STA		ARY,X
		RMO		B,A
		MUL		#3
		RMO		A,X
		STT		ARY,X
CONFIG	LDA		#1
		ADDR	A,B
		STB		IXD
		ADDR	B,A
		RMO		A,S
		RMO		B,A
		MUL		#3
		RMO		A,X
		LDA		ARY,X
		STA		IXE
		RMO		A,T
		STA		TA
		STB		TB
		STS		TS
		STT		TT
		JSUB	STATE
		LDA		TA
		LDB		TB
		LDS		TS
		LDT		TT
		J		SELF

RET		J		ESORT	

STDIN	BYTE	0					// STDIN Constance
STDOUT	BYTE	1					// STDOUT Constance
ENTER 	WORD	1					// PRINT Constance
SEP		WORD	32					// Input Separation
ETR		WORD	10					// Enter
WRD		WORD	3					// Separate Word
EOF		BYTE	C'EOF'				// End of Input Constance
ERR		BYTE	C'ERROR'
IXA		WORD	0
IXB		WORD	0					// Num of Inputs
IXC		WORD	0
IXD		WORD	0					// End of Sort Array
IXE		WORD	0
TA		WORD	0
TB		WORD	0
TS		WORD	0
TT		WORD	0
ARY		RESW	8
TEMP	WORD	0
BUFFER	RESB	3
NUMFIR	WORD	48
NUMEND	WORD	57

ERROR	CLEAR	X
		RMO		X,A
ERRORL	COMP	#5
		JEQ		ERRORE
		LDCH	ERR,X
ERRORT	TD		STDOUT
		JEQ		ERRORT
		WD		STDOUT
		LDA		#1
		ADDR	A,X
		RMO		X,A
		J		ERRORL
		
ERRORE	JSUB	PRINTE
		END		SORT
