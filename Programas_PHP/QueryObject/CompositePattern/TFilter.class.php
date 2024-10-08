<?php

/*
*   Classe TFilter
*   Esta classe provê a interface para definição de filtros de seleção
*/

class TFilter extends TExpression 
{
    private $variable; // variavel
    private $operator; // operador
    private $value; // valor

    /**
     *   Método __construct()
     *   instancia um novo filtro
     *   @param $variable = variável
     *   @param $operator = operador (>,<)
     *   @param $value = valor a ser comparado
    */

    public function __construct($variable, $operator, $value)
    {
        $this->variable = $variable;
        $this->operator = $operator;
        $this->value = $value;

        // tranforma o valor de acordo com certas regras
        // antes de atribuir a propriedade $this->value

        $this->value = $this->transform($value);
    }

    /**
     *   Método Transform()
     *   recebe o valor e faz as modificações necessárias
     *   para ele ser implementado pelo banco de dados
     *   podendo ser um integer,string,boolean ou array
     *   @param $value = valor a ser transformado
    */

    private function transform($value) {
        // caso seja um array
        if (is_array($value)) {
            // percorre os valores
            foreach ($value as $x) {
                if(is_integer($x)) {
                    // se for inteiro
                    $foo[] = $x;
                } else if (is_string($x)) {
                    // se for string adiciona aspas
                    $foo[] = "'$x'";
                }
            }
            // converte o array em string separada por ","
            $result = '('.implode(separator: ', ', array: $foo).')';
        }
        // caso seja uma string
        else if (is_string($value)) {
            // adiciona aspas
            $result = "$value";
        }
        // caso seja um valor nulo
        else if (is_null($value)) {
            // armazena nulo
            $result = 'NULL';
        }
        // caso seja um boleano
        else if (is_bool($value)) {
            // armazena TRUE ou FALSE
            $result = $value ?'true':'false';
        }
        else {
            $result = $value;
        }
        // retorna o valor
        return $result;
    }

    /**
     *   Método dump()
     *   retorna o filtro em forma de expressão
    */

    public function dump() {
        // concatena a expressão
        return "{$this->variable} {$this->operator} {$this->value}";
    }
}