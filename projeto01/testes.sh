#! /bin/bash

# Referências:
# https://stackoverflow.com/questions/385408/get-program-execution-time-in-the-shell - Calcular tempo de execução usando bash

# compile code and execute tests

gcc ./escada_rolante_threads.c -o threads.bin -lpthread
gcc ./escada_rolante_processos.c -o processos.bin

find . -name "result.txt" -delete
FILES=$(ls ./input/)
OUTPUT_FOLDER="./output/"

for FILE in $FILES; do
	START=$(date +%s.%N)
	RESULT_THREAD=$(./threads.bin ./input/$FILE)
	DIFF=$(echo "$(date +%s.%N) - $START" | bc)
	EXPECTED=$(head -n 1 $OUTPUT_FOLDER$FILE)
	echo "Testando arquivo $FILE utilizando threads (Tempo de execução: $DIFF)"
	if [[ $RESULT_THREAD -ne $EXPECTED ]]; then
		echo "($FILE) teste com threads falhou (Esperado: $EXPECTED) (RESULTADO: $RESULT_THREAD)" >>result.txt
	fi
done

for FILE in $FILES; do
	START=$(date +%s.%N)
	RESULT_PROCESS=$(./processos.bin ./input/$FILE)
	DIFF=$(echo "$(date +%s.%N) - $START" | bc)
	EXPECTED=$(head -n 1 $OUTPUT_FOLDER$FILE)
	echo "Testando arquivo $FILE utilizando processos (Tempo de execução: $DIFF)"
	if [[ $RESULT_PROCESS -ne $EXPECTED ]]; then
		echo "($FILE) teste com processos falhou (Esperado: $EXPECTED) (RESULTADO: $RESULT_PROCESS)" >>result.txt
	fi

done
