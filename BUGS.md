BUGS
====

List of known bugs.

If you know a bug that is not here, add it!

Currently Open Bugs
--------------------

A RESPOSTA DESSAS DUAS ACHO Q EH PQ MOVE_TABLE NEM SEMPRE EH FICAR PARADO
- Mesmo com o oponente apenas com a opcao de move_table (ficar parado) a best_action do minmax define uma posicao que n�o � a dele (ficar parado).
- Quando jogo todos os oponentes para fora, embora na visao (entrada pro minmax) os oponentes estejam fora o move do ultimo a ser removido cai dentro do campo, pq?

- DriveToBall ainda est� demorando para fazer a voltinha e as vezes ele trava.
- Pq quando ele t� longe da bola as vezes ele prefere um move do que um get_ball ????
- No minmax rob�s ficam saindo do campo, pq?
- Condi��o para gerar estabilidade no minmax ainda n�o est� legal no AttackerMinMax2
- Rotina de pesar por alterar move do minmax n�o est� funcionando (acho q melhor n�o � pesar por alterar e sim por gerar instabilidade).
- Melhorar a arquitetura do LinearCombMotion e DriveToball, pois s�o skills contendo skills, o que dificulta o uso do setRobot.
- Finalizar o GotoAvoid.
- Rob� n�o deve chutar enquanto o dribble estiver e a bola estiver na inercial do giro do driblador.
- Minmax n�o segue as regras do jogo(comando do juiz e n�o colidir)
- Zicker43 s� chuta no meio do gol.
- Minmax n�o chuta no meio do maior buraco.
- Goto demora para atingir a posi��o final, ficando lento quando
  est� chegando perto (no Goto poderia ser passado a velocidade final desejada), e fazer um controle conceitualmente correto.
- Controller2 o rob� n�o est� mais olhando fixamente para bola.
- SampledKick::calculatePassPower n�o funciona para um vFin gen�rico.
- Simulador est� descasado do campo/rob�/bola real.

