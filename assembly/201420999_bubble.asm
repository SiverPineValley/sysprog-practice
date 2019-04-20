SORT	START	0
		J		INPUT
EINPUT	J		BUBBLE
ESORT	END		SORT
	
INPUT	RD		STDIN				// 5개의 숫자 입력
		COMP	SEP
		JEQ		TSAVE
		COMP	ETR
		JEQ		TSAVE
		COMP	#69
		JEQ		CEND
		JSUB	CKBYTE
		SUB		#48
		ADD		TEMP
		MUL		#10
		STA		TEMP
		CLEAR	A
		J		INPUT

TSAVE	LDA		TEMP				// 수 저장
		DIV		#10
		STA		ARY,X
		LDA		WRD
		ADDR	A,X
		LDA		IXB
		ADD		#1
		STA		IXB
		CLEAR	A
		STA		IXA
		STA		TEMP
		J		INPUT

CKBYTE	RMO		A,S					// 각 수의 자리 확인
		CLEAR	A
		LDA		IXA
		COMP	#5
		JEQ		TSAVE
		ADD		#1
		STA		IXA
		CLEAR	A
		RMO		S,A
		CLEAR	S
		RSUB

CEND	LDX		#0
		STCH	BUFFER,X
SLOOP	LDA		#1		
		ADDR	A,X
		CLEAR	A
		RD		STDIN
		COMP	ETR
		JEQ		EINPUT
		STCH	BUFFER,X
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

BUBBLE	LDA		IXB
		SUB		#1
		STA		IXD
BLOOP	COMP	#0					// IXD == 0이면, SORT 끝
		JEQ		RET
		CLEAR	S
SOLOOP	COMPR	A,S					// S는 현재 index. A는 IXD.
		JEQ		EES
		CLEAR	A					// A에 현 ARY 불러와서 T에 저장. 
		ADDR	S,A
		MUL		#3
		RMO		A,X
		LDT		ARY,X
		LDA		#3					// A에는 다음 ARY를 불러온다.
		ADDR	A,X
		LDA		ARY,X
		COMPR	A,T					// 비교
		JLT		TISB				// T(현재 값)이 더 클 때
		J		AISB
TISB	STT		ARY,X
		RMO		A,T
		LDA		#3
		SUBR	A,X
		STT		ARY,X
AISB	LDA		#1
		ADDR	A,S
		LDA		IXD
		J		SOLOOP
		
EES		LDA		IXD					// 각 Sort의 State 마무리
		SUB		#1
		STA		IXD
		CLEAR	T
		CLEAR	A
		CLEAR	X
		JSUB	STATE
		CLEAR	S
		LDA		IXD
		J		BLOOP

RET		J		ESORT	

STDIN	BYTE	0					// STDIN Constance
STDOUT	BYTE	1					// STDOUT Constance
ENTER 	WORD	1					// PRINT Constance
SEP		WORD	32					// Input Separation
ETR		WORD	10					// Enter
WRD		WORD	3					// Separate Word
EOF		BYTE	C'EOF'				// End of Input Constance
IXA		WORD	0
IXB		WORD	0					// Num of Inputs
IXC		WORD	0
IXD		WORD	0					// End of Sort Array
ARY		RESW	8
TEMP	WORD	0
BUFFER	RESB	3
