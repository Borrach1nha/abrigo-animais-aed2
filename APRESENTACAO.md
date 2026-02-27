Primeiramente gostaríamos de agradecer ao Prof Dr. Renan Vinicius Aranha pelas aulas ministradas e por todo o capricho nos conteúdos disponibilizados, é uma honra ser discente de um excelente profissional como ele

Nosso tema é um sistema de gerenciamento de abrigo de animais, onde o usuário que passa por uma autenticação prevista no arquivo "usuario.csv", é capaz de cadastrar, listar, editar, remover e pesquisar animais no sistema

Nosso sistema conta com funcionalidades que trata algumas exceções, como não sendo possível inserir idade negativa, não sendo possível deletar um animal com ID incorreto, não sendo possível adicionar caracteres em campos que solicitam números etc.

Os dados dos animais são gravados no arquivo "base.csv", onde cada animal respeita o padrão "id,nome,especie,idade"

Toda ação é registrada e armazenada no arquivo "logs.csv" que diz qual usuário e que ação ele fez

O arquivo "saida.csv" apenas mostra qual saída o programa devolveu ao usuário quando o mesmo faz o uso da função pesquisar

A lógica do programa principal está contido no arquivo dados.c e dados.h e usamos majoritariamente structs para isso

No demais, esse é o nosso sistema que criamos, espero que gostem!