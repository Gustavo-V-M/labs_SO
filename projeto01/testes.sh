#! /bin/bash

# compile thread code and execute tests

g++ ./escada_rolante_threads.cpp -o threads.out

FILES=$(ls ./input/)
OUTPUT_FOLDER="./output/"

for FILE in $FILES; do
	echo "Testando arquivo $FILE"
	RESULT=$(./threads.out ./input/$FILE)
	EXPECTED=$(head -n 1 $OUTPUT_FOLDER$FILE)
	if [[ $RESULT -ne $EXPECTED ]]; then
		echo "($FILE) teste falhou (Esperado: $EXPECTED) (RESULTADO: $RESULT)" >>result.txt
	fi
done
