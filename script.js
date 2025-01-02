// script.js

// Solution array (same as the one in C)
const solution = [
    ["H", "e", "l", "l", "o"],
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

// Initialize the grid on page load
createGrid();
