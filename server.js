const express = require('express');
const bodyParser = require('body-parser');
const app = express();
const port = 3000;

// Middleware
app.use(bodyParser.json());
app.use(express.static('frontend'));

// POST endpoint for scheduling tasks
app.post('/schedule', (req, res) => {
    const tasks = req.body.tasks;

    // Placeholder for scheduling logic and stats calculation
    const stats = calculateStatistics(tasks);

    // Respond with computed stats
    res.json(stats);
});

// Dummy function to calculate stats (replace with actual logic)
function calculateStatistics(tasks) {
    // Example stats (replace with actual calculation)
    return {
        fcfsStats: {
            averageWaitingTime: Math.random() * 10,
            averageTurnaroundTime: Math.random() * 20
        },
        sjnStats: {
            averageWaitingTime: Math.random() * 10,
            averageTurnaroundTime: Math.random() * 20
        },
        priorityStats: {
            averageWaitingTime: Math.random() * 10,
            averageTurnaroundTime: Math.random() * 20
        }
    };
}

// Start server
app.listen(port, () => {
    console.log(`Server running at http://localhost:${port}`);
});


