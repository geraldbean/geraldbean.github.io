// script.js

// Solution array (same as the one in C)
const solution = [
    ["b", "r", "o", "w", "n"],
    ["E", "a", "r", "t", "h"],
    ["H", "a", "z", "e", "l"],
    ["A", "n", "g", "i", "e"],
    ["f", "r", "o", "w", "n"]
];

// Create the crossword grid dynamically
const gridContainer = document.getElementById("grid-container");

function createGrid() {
    for (let row = 0; row < 5; row++) {
        for (let col = 0; col < 5; col++) {
            const input = document.createElement("input");
            input.type = "text";
            input.maxLength = 1; // Only one character per cell
            input.dataset.row = row;
            input.dataset.col = col;
            input.addEventListener("input", onInputChange);
            gridContainer.appendChild(input);
        }
    }
}

// Handle user input
function onInputChange(event) {
    const input = event.target;
    const row = input.dataset.row;
    const col = input.dataset.col;

    const userInput = input.value.toUpperCase();
    const correctAnswer = solution[row][col].toUpperCase();

    // Check if the answer is correct
    if (userInput === correctAnswer) {
        input.style.backgroundColor = "lightgreen";
    } else if (userInput !== "") {
        input.style.backgroundColor = "lightcoral";
    } else {
        input.style.backgroundColor = "";
    }
}

// Move to the next cell when an arrow key is pressed
function moveToNextCell(event) {
    let nextRow = currentRow;
    let nextCol = currentCol;

    switch (event.key) {
        case "ArrowUp":
            if (currentRow > 0) nextRow--;
            break;
        case "ArrowDown":
            if (currentRow < 4) nextRow++;
            break;
        case "ArrowLeft":
            if (currentCol > 0) nextCol--;
            break;
        case "ArrowRight":
            if (currentCol < 4) nextCol++;
            break;
        default:
            return; // Do nothing if it's not an arrow key
    }

    // Update the active cell's focus
    currentRow = nextRow;
    currentCol = nextCol;
    const nextInput = document.querySelector(`[data-row='${currentRow}'][data-col='${currentCol}']`);
    nextInput.focus();
}

// Check all answers when the "Check Answers" button is clicked
document.getElementById("check-button").addEventListener("click", function() {
    const inputs = document.querySelectorAll("#grid-container input");

    inputs.forEach(input => {
        const row = input.dataset.row;
        const col = input.dataset.col;
        const userInput = input.value.toUpperCase();
        const correctAnswer = solution[row][col].toUpperCase();

        if (userInput === correctAnswer) {
            input.style.backgroundColor = "lightgreen";
        } else {
            input.style.backgroundColor = "lightcoral";
        }
    });
});

//look for arrow key being presssed
window.addEventListener("keydown", moveToNextCell);

// Initialize the grid on page load
createGrid();
