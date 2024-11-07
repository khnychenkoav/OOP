document.addEventListener('DOMContentLoaded', () => {
    Module.onRuntimeInitialized = () => {
        initialize();
    };
});

let currentType = 'int';
let chart;

function initialize() {
    Module.create_list('int');
    Module.create_list('string');
    setupEventListeners();
    initializeCharts();
    drawList();
    updateMemoryInfo();
}

function setupEventListeners() {
    document.getElementById('dataType').addEventListener('change', (e) => {
        currentType = e.target.value;
        drawList();
    });

    document.getElementById('pushBackBtn').addEventListener('click', pushBack);
    document.getElementById('pushFrontBtn').addEventListener('click', pushFront);
    document.getElementById('popBackBtn').addEventListener('click', popBack);
    document.getElementById('popFrontBtn').addEventListener('click', popFront);
    document.getElementById('clearBtn').addEventListener('click', clearList);
    document.getElementById('sortBtn').addEventListener('click', sortList);
    document.getElementById('searchBtn').addEventListener('click', searchValue);
    document.getElementById('themeToggle').addEventListener('click', toggleTheme);
}

function toggleTheme() {
    document.body.classList.toggle('dark-theme');
    const themeToggleBtn = document.getElementById('themeToggle');
    themeToggleBtn.textContent = document.body.classList.contains('dark-theme') ? '☀️' : '🌙';
}

function drawList() {
    const listContents = getListContents();
    const container = document.getElementById('listContainer');
    container.innerHTML = '';
    const size = listContents.size();
    for (let i = 0; i < size; i++) {
        const value = listContents.get(i);
        const node = document.createElement('div');
        node.classList.add('node');
        node.innerHTML = `
            <span class="value">${value}</span>
            <div class="pointer next">→</div>
        `;
        node.title = `Index: ${i}\nValue: ${value}`;
        container.appendChild(node);
        setTimeout(() => {
            node.classList.add('visible');
        }, i * 100);
    }
    updateMemoryInfo();
    updateCharts();
}

function getListContents() {
    return currentType === 'int' ? Module.get_list_contents_int() : Module.get_list_contents_string();
}

function pushBack() {
    const value = document.getElementById('inputValue').value;
    if (currentType === 'int') {
        const intValue = parseInt(value);
        if (!isNaN(intValue)) {
            Module.push_back_int(intValue);
            drawList();
        }
    } else {
        Module.push_back_string(value);
        drawList();
    }
}

function pushFront() {
    const value = document.getElementById('inputValue').value;
    if (currentType === 'int') {
        const intValue = parseInt(value);
        if (!isNaN(intValue)) {
            Module.push_front_int(intValue);
            drawList();
        }
    } else {
        Module.push_front_string(value);
        drawList();
    }
}

function popBack() {
    currentType === 'int' ? Module.pop_back_int() : Module.pop_back_string();
    drawList();
}

function popFront() {
    currentType === 'int' ? Module.pop_front_int() : Module.pop_front_string();
    drawList();
}

function clearList() {
    Module.clear_all();
    Module.create_list('int');
    Module.create_list('string');
    drawList();
}

function sortList() {
    currentType === 'int' ? Module.sort_list_int() : Module.sort_list_string();
    drawList();
}

function searchValue() {
    const value = document.getElementById('inputValue').value;
    let found = false;
    if (currentType === 'int') {
        const intValue = parseInt(value);
        if (!isNaN(intValue)) {
            found = Module.search_list_int(intValue);
        }
    } else {
        found = Module.search_list_string(value);
    }
    alert(`Value "${value}" ${found ? 'found' : 'not found'} in the list.`);
}

function updateMemoryInfo() {
    const allocatedBlocks = Module.get_allocated_blocks();
    const freeBlocks = Module.get_free_blocks();
    const memoryInfoDiv = document.getElementById('memoryInfo');
    memoryInfoDiv.innerHTML = `
        <strong>Allocated Blocks:</strong> ${allocatedBlocks.size()} <br>
        <strong>Free Blocks:</strong> ${freeBlocks.size()}
    `;
    memoryInfoDiv.title = `Total Allocated Blocks: ${allocatedBlocks.size()}\nTotal Free Blocks: ${freeBlocks.size()}`;
}

function initializeCharts() {
    const ctx = document.getElementById('memoryChart').getContext('2d');
    chart = new Chart(ctx, {
        type: 'pie',
        data: {
            labels: ['Allocated Blocks', 'Free Blocks'],
            datasets: [{
                data: [0, 0],
                backgroundColor: ['#ff6347', '#32cd32'],
            }]
        },
        options: {
            responsive: true,
            maintainAspectRatio: false,
            onClick: showMemoryDetails,
            plugins: {
                tooltip: {
                    callbacks: {
                        label: function(context) {
                            let label = context.label || '';
                            let value = context.formattedValue || '0';
                            return `${label}: ${value}`;
                        }
                    }
                }
            }
        }
    });
}

function updateCharts() {
    const allocatedBlocks = Module.get_allocated_blocks();
    const freeBlocks = Module.get_free_blocks();
    chart.data.datasets[0].data = [allocatedBlocks.size(), freeBlocks.size()];
    chart.update();
}

function showMemoryDetails(event, elements) {
    if (elements && elements.length) {
        const index = elements[0].index;
        const label = chart.data.labels[index];
        let blocks = label === 'Allocated Blocks' ? Module.get_allocated_blocks() : Module.get_free_blocks();
        let details = `${label} Details:\n`;
        for (let i = 0; i < blocks.size(); i++) {
            const block = blocks.get(i);
            details += `Block ${i + 1} - Pointer: ${block.pointer}, Size: ${block.size} bytes, Alignment: ${block.alignment}\n`;
        }
        alert(details);
    }
}
