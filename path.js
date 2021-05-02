function create_matrix() {
    let string = '';
    let exists = false;
    for (let node in data.nodes){
        for (let node_2 in data.nodes){
            if (node == node_2 || (!data.nodes[node].id in matrix)){
                string = string.concat(" ", "0")
            } else {
                for (let info in matrix[data.nodes[node].id]){
                    if (matrix[data.nodes[node].id][info].to == data.nodes[node_2].id){
                        string = string.concat(" ", matrix[data.nodes[node].id][info].length)
                        exists = true
                    }
                }
                if (!exists){
                    string = string.concat(" ", "0")
                }
                exists = false
            }
        }
    }
    return string
}

$( "#create-path" ).click(function() {
    Module.onRuntimeInitialized = async _ => {
        const api = {
            version: Module.cwrap('main_fun', 'number', ['number', 'string']),
        };
        const matrix_to_string = create_matrix();
        let nose = api.version(data.nodes.length, matrix_to_string.trim())
        console.log(nose)
    
    };
    Module.onRuntimeInitialized();
});