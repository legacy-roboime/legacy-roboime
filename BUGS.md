BUGS
====

List of known bugs.

If you know a bug that is not here, add it!

Currently Open Bugs
--------------------
- no gotoavoid para evitar ficar travando na hora de fazer a volta, a melhor solucao seria usar dois circulos concetricos para definir o estado de transicao.
- move_table � incompleta, pois n�o tenho todas as informa��es necess�rias para executar a action anterior (s� tem posicao)

A RESPOSTA DESSAS DUAS ACHO Q EH PQ MOVE_TABLE NEM SEMPRE EH FICAR PARADO
- Mesmo com o oponente apenas com a opcao de move_table (ficar parado) a best_action do minmax define uma posicao que n�o � a dele (ficar parado).
- Quando jogo todos os oponentes para fora, embora na visao (entrada pro minmax) os oponentes estejam fora o move do ultimo a ser removido cai dentro do campo, pq?

- Pq quando ele t� longe da bola as vezes ele prefere um move do que um get_ball ????
- No minmax rob�s ficam saindo do campo, pq?
- Minmax n�o chuta no meio do maior buraco.
- Condi��o para gerar estabilidade no minmax ainda n�o est� legal no AttackerMinMax2
- pesar na escolha do minmax em fun�ao da variacao do angulo de destino e n�o a variacao da distancia do ponto de destino

- Minmax n�o segue as regras do jogo(comando do juiz e n�o colidir)
- Minmax tem q receber qual eh o goleiro para soh ele poder querer entrar na area.
- Minmax conduz a bola acima do permitido.

- DriveToBall ainda est� demorando para fazer a voltinha e as vezes ele trava (testar no real).
- Finalizar o GotoAvoid.
- Zicker43 s� chuta no meio do gol.
- Melhorar a arquitetura do LinearCombMotion e DriveToball, pois s�o skills contendo skills, o que dificulta o uso do setRobot.
- Rob� n�o deve chutar enquanto o dribble estiver e a bola estiver na inercial do giro do driblador.
- Goto demora para atingir a posi��o final, ficando lento quando
  est� chegando perto (no Goto poderia ser passado a velocidade final desejada), e fazer um controle conceitualmente correto.
- Controller2 o rob� n�o est� mais olhando fixamente para bola.
- SampledKick::calculatePassPower n�o funciona para um vFin gen�rico.
- Simulador est� descasado do campo/rob�/bola real.

