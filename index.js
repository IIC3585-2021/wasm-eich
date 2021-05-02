

const matrix = {}
var data = {
    nodes: [],
    edges: []
};


$( "#add-vector" ).click(function() {
    let text = $("#new-vector").val();
    const input = text.split(" ");
    if (input.length !== 3){
        alert("No ingresaste de buena manera tu input. Recuerda que es Nodo Nodo Peso")
    } else {
    let from = input[0]
    let to = input[1]
    let length = input[2]
    if (from in matrix) {
        matrix[from].push({to: to, length: length})
    } else {
        matrix[from] = [{to: to, length: length}]
    }
    if (!(data.nodes.some(person => person.id === from))) {
        data.nodes.push({id: from})
    } 
    if (!(data.nodes.some(person => person.id === to))) {
        data.nodes.push({id: to})
    } 
    data.edges.push({from: from, to: to})
    $("#vectors").append(`<li><span class="tab">From:${from} To:${to} Length:${length}</span></li>`);
  }});
$( "#create-graph" ).click(function() {
    var chart = anychart.graph(data);

    // enable labels of nodes
    chart.nodes().labels().enabled(true);

    // set the container id
    chart.container("chart");

    // initiate drawing the chart
    chart.draw();
});


