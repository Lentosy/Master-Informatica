let messageHolder;
let socket;
let roundNumber;
let gameWindow;
let gameresultWindow;

/*
 * Initialise the websocket after the webpage has succesfully loaded
 */
window.onload = function () {
    gameresultWindow = document.querySelector("#gameresultWindow");
    gameWindow = document.querySelector("#gameWindow");
    roundNumber = document.querySelector("#roundnumber"); // to display current round
    messageHolder = document.querySelector("#messageHolder"); // to display messages
    socket = new WebSocket("ws://localhost:8084/Prisoners_Dilemma/game");
    socket.addEventListener('error', function (event) {
        handleSocketError(event);
    });
    socket.addEventListener('open', function (event) {
        handleSocketOpen(event);
    });
    socket.addEventListener('message', function (event) {
        handleSocketMessage(event);
    });
};

/**
 * Starts a new game of prisoners dilemma.
 * @param {String} against a String from {'player', 'computer'}
 * @param {String} username The name of the user
 * @returns {undefined}
 */
function startGame(against, username) {
    let newGame = {
        GAMEMODE: against,
        PLAYERNAME: username
    };

    let menu = document.querySelector("#menu");
    menu.hidden = true;
    gameWindow.hidden = false;

    let gameButtons = document.querySelector("#gameButtons");
    gameButtons.childNodes.forEach(function (button) {
        button.addEventListener('click', function (event) {
            let decision = button.dataset.decision;
            sendDecision(decision);
        });
    });
    setMessage("Game started against " + against);
    socket.send(JSON.stringify(newGame));
}

/**
 * 
 * @param {type} decision A decision from {0, 1}, 0 meaning confess and 1 meaning remain silent
 * @returns {undefined}
 */
function sendDecision(decision) {
    let operation = {
        PLAYER_DECISION: parseInt(decision)
    };
    socket.send(JSON.stringify(operation));
}

/**
 * Sets the innerHTML property of the messageHolder object
 * 
 * @param {type} message The message to be set
 * @returns {undefined}
 */
function setMessage(message) {
    messageHolder.innerHTML = message;
}

/**
 * Gets called when a socket connection opened succesfully. 
 * This method will initialize the GUI.
 * @param {type} event
 * @returns {undefined}
 */
function handleSocketOpen(event) {
    setMessage("Connection open, please stand by...");
    let menu = document.querySelector("#menu");
    menu.hidden = false;
    let startButtons = document.querySelector("#startButtons");
    let usernameInput = document.querySelector("#userinput");
    startButtons.childNodes.forEach(function (button) {
        button.addEventListener('click', function (event) {
            let username = usernameInput.value;
            if (username.length === 0) {
                alert("Enter a username");
            } else {
                let against = button.dataset.against;
                startGame(against, username);
            }
        });
    });
}

/**
 * Gets called when a socket connection error occured.
 * @param {type} event
 * @returns {undefined}
 */
function handleSocketError(event) {
    console.log(event);
    setMessage("Could not connect to the server! Please refresh your browser.");
}

/**
 * 
 * @param {type} event 
 */
function handleSocketMessage(event) {
    let message = JSON.parse(event.data);
    console.log(message);
    if (message["ROUND_RESULT"]) {
        setMessage(message["ROUND_RESULT"]);
        roundNumber.innerHTML = message["ROUND"] + 1;
    } else if (message["GAMESTATUS"]) {
        setMessage(message["GAMESTATUS"]);
    } else if (message["END_GAME"]) {
        gameWindow.hidden = true;
        gameresultWindow.hidden = false;
        let gameresult = JSON.parse(message["END_GAME"]);
        var player1 = gameresult.player;
        var player2 = gameresult.player2;
        document.querySelector("#name_player_one").innerHTML = player1.name;
        document.querySelector("#name_player_two").innerHTML = player2.name;
        var html = "";
        for (var i = 0; i < 30; i++) {
            html += "<tr>";
            html += "<td>" + (i + 1) + "</td>";
            html += "<td>" + (player1.choiceHistory[i] === 1 ? "remained silent" : "confessed") + "</td>";
            html += "<td>" + getYearsToServe(player1.choiceHistory[i], player2.choiceHistory[i]) + " year(s)</td>";
            html += "<td>" + (player2.choiceHistory[i] === 1 ? "remained silent" : "confessed") + "</td>";
            html += "<td>" + getYearsToServe(player2.choiceHistory[i], player1.choiceHistory[i]) + " year(s)</td>";
            html += "</tr>\n";
        }

        document.querySelector("#results").innerHTML = html;
    }
}

/*
 * Geeft het aantal jaar dat de speler met keuze 'x' gemaakt heeft
 * Keuze 'y' is dan van de tegenstander
 */
function getYearsToServe(x, y) {
    if (x === 1 && y === 1) { // both remain silent
        return 1;
    }

    if (x === 1 && y === 0) { //
        return 3;
    }

    if (x === 0 && y === 1) { //
        return 0;
    }

    return 2;
}