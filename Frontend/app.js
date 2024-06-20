let tasks = [];
let statsChart; // Define statsChart globally

function addTask() {
    const arrivalTime = document.getElementById('arrivalTime').value;
    const burstTime = document.getElementById('burstTime').value;
    const priority = document.getElementById('priority').value;

    // Create a new task object
    const newTask = {
        arrivalTime: parseInt(arrivalTime, 10),
        burstTime: parseInt(burstTime, 10),
        priority: parseInt(priority, 10)
    };

    // Add the new task to the tasks array
    tasks.push(newTask);

    // Clear the form fields
    document.getElementById('arrivalTime').value = '';
    document.getElementById('burstTime').value = '';
    document.getElementById('priority').value = '';

    // Render the tasks list
    renderTasks();
}

function renderTasks() {
    const tasksDiv = document.getElementById('tasks');
    tasksDiv.innerHTML = ''; // Clear existing tasks

    tasks.forEach((task, index) => {
        const taskItem = document.createElement('div');
        taskItem.className = 'task-item';
        taskItem.innerHTML = `
            <p>Task ${index + 1}: Arrival Time = ${task.arrivalTime}, Burst Time = ${task.burstTime}, Priority = ${task.priority}</p>
        `;
        tasksDiv.appendChild(taskItem);
    });
}

function scheduleTasks() {
    fetch('/schedule', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({ tasks })
    })
        .then(response => response.json())
        .then(data => {
            console.log('Response from server:', data); // Log the response from the server
            displayStats(data); // Ensure this is correctly called
            displayTable(data); // Display the results in a table
        })
        .catch(error => console.error('Error:', error));
}

function displayStats(data) {
    const ctx = document.getElementById('statsChart').getContext('2d');

    // Check if statsChart exists and destroy it before creating a new one
    if (statsChart) {
        statsChart.destroy();
    }

    // Create a new chart instance
    statsChart = new Chart(ctx, {
        type: 'bar',
        data: {
            labels: ['FCFS', 'SJN', 'Priority'],
            datasets: [
                {
                    label: 'Average Waiting Time',
                    data: [
                        data.fcfsStats.averageWaitingTime.toFixed(2),
                        data.sjnStats.averageWaitingTime.toFixed(2),
                        data.priorityStats.averageWaitingTime.toFixed(2)
                    ],
                    backgroundColor: [
                        'rgba(54, 162, 235, 0.8)', // Brighter blue
                        'rgba(54, 162, 235, 0.8)',
                        'rgba(54, 162, 235, 0.8)'
                    ],
                    borderColor: [
                        'rgba(54, 162, 235, 1)',
                        'rgba(75, 192, 192, 1)',
                        'rgba(255, 206, 86, 1)'
                    ],
                    borderWidth: 1
                },
                {
                    label: 'Average Turnaround Time',
                    data: [
                        data.fcfsStats.averageTurnaroundTime.toFixed(2),
                        data.sjnStats.averageTurnaroundTime.toFixed(2),
                        data.priorityStats.averageTurnaroundTime.toFixed(2)
                    ],
                    backgroundColor: [
                        'rgba(255, 99, 132, 0.8)', // Brighter red
                        'rgba(255, 99, 132, 0.8)',
                        'rgba(255, 99, 132, 0.8)'
                    ],
                    borderColor: [
                        'rgba(255, 99, 132, 1)',
                        'rgba(153, 102, 255, 1)',
                        'rgba(255, 159, 64, 1)'
                    ],
                    borderWidth: 1
                }
            ]
        },
        options: {
            scales: {
                y: {
                    beginAtZero: true
                }
            },
            responsive: true,
            plugins: {
                legend: {
                    position: 'top'
                },
                tooltip: {
                    mode: 'index',
                    intersect: false
                }
            },
            interaction: {
                mode: 'nearest',
                axis: 'x',
                intersect: false
            }
        }
    });
}

function displayTable(data) {
    const tableDiv = document.getElementById('resultsTable');
    tableDiv.innerHTML = ''; // Clear existing table

    const table = document.createElement('table');
    table.className = 'results-table';
    table.innerHTML = `
        <thead>
            <tr>
                <th>Algorithm</th>
                <th>Average Waiting Time</th>
                <th>Average Turnaround Time</th>
            </tr>
        </thead>
        <tbody>
            <tr>
                <td>FCFS</td>
                <td>${data.fcfsStats.averageWaitingTime.toFixed(2)}</td>
                <td>${data.fcfsStats.averageTurnaroundTime.toFixed(2)}</td>
            </tr>
            <tr>
                <td>SJN</td>
                <td>${data.sjnStats.averageWaitingTime.toFixed(2)}</td>
                <td>${data.sjnStats.averageTurnaroundTime.toFixed(2)}</td>
            </tr>
            <tr>
                <td>Priority</td>
                <td>${data.priorityStats.averageWaitingTime.toFixed(2)}</td>
                <td>${data.priorityStats.averageTurnaroundTime.toFixed(2)}</td>
            </tr>
        </tbody>
    `;

    tableDiv.appendChild(table);

    // Determine the optimal algorithm based on minimum average waiting time
    const optimalAlgorithm = determineOptimalAlgorithm(data);
    const optimalDiv = document.createElement('div');
    optimalDiv.className = 'optimal-result';
    optimalDiv.innerHTML = `<p>Optimal Algorithm: <strong>${optimalAlgorithm}</strong></p>`;
    tableDiv.appendChild(optimalDiv);
}

function determineOptimalAlgorithm(data) {
    const algorithms = ['FCFS', 'SJN', 'Priority'];
    const waitingTimes = [
        data.fcfsStats.averageWaitingTime,
        data.sjnStats.averageWaitingTime,
        data.priorityStats.averageWaitingTime
    ];

    const minWaitingTime = Math.min(...waitingTimes);
    const optimalIndex = waitingTimes.indexOf(minWaitingTime);
    return algorithms[optimalIndex];
}




