/*
GAME RULES:

- The game has 2 players, playing in rounds
- In each turn, a player rolls a dice as many times as he whishes. Each result get added to his ROUND score
- BUT, if the player rolls a 1, all his ROUND score gets lost. After that, it's the next player's turn
- The player can choose to 'Hold', which means that his ROUND score gets added to his GLBAL score. After that, it's the next player's turn
- The first player to reach 100 points on GLOBAL score wins the game

*/

var scores, roundScore, activePlayer;

newGame();



document.querySelector('.btn-roll').addEventListener('click', function () {
    var dice = Math.ceil(Math.random() * 6);
    
    var diceDO = document.querySelector('.dice');
    diceDO.style.display = 'block';
    diceDO.src = 'dice-' + dice + '.png';

    var currentScoreDOM = document.querySelector('#current-' + activePlayer);
    currentScoreDOM.textContent = roundScore;
    if (dice !== 1) {
        roundScore += dice;
    } else {
        roundScore = 0;
        currentScoreDOM.textContent = roundScore;

        nextPlayer();
    }

    currentScoreDOM.textContent = roundScore;
    
});
document.querySelector('.btn-hold').addEventListener('click', function () {
    scores[activePlayer] += roundScore;
    document.querySelector('#score-' + activePlayer).textContent = scores[activePlayer];
    
    roundScore = 0;
    var currentScoreDOM = document.querySelector('#current-' + activePlayer);
    currentScoreDOM.textContent = roundScore;
    
    if (scores[activePlayer] >= 100) {
        document.querySelector('#name-' + activePlayer).textContent = 'WINNNER!!';
        document.querySelector('.player-' + activePlayer + '-panel').classList.add('winner');
        document.querySelector('.player-' + activePlayer + '-panel').classList.remove('active');
        
    } else {
        nextPlayer();
    }
});
function nextPlayer() {
    activePlayer === 0 ? activePlayer = 1 : activePlayer = 0;
    document.querySelector('.player-0-panel').classList.toggle('active');
    document.querySelector('.player-1-panel').classList.toggle('active');
    document.querySelector('.dice').style.display = 'none';
}

document.querySelector('.btn-new').addEventListener('click', newGame);

function newGame() {
    scores = [0,0];
    activePlayer = 0;
    roundScore = 0;    
    document.querySelector('.dice').style.display = 'none';
    document.querySelector('#score-0').textContent = scores[0];
    document.querySelector('#score-1').textContent = scores[1];
    document.querySelector('#name-0').textContent = 'Player 1';
    document.querySelector('#name-1').textContent = 'Player 2';
    document.querySelector('.player-0-panel').classList.remove('active');
    document.querySelector('.player-0-panel').classList.add('active');
    document.querySelector('.player-1-panel').classList.remove('active');
    document.querySelector('.player-0-panel').classList.remove('winner');
    document.querySelector('.player-1-panel').classList.remove('winner');
}