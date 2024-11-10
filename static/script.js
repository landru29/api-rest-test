$(() => {
    console.log( 'ready!' );

    fetch('/read')
        .then((response)=>response.json())
        .then((data)=>{
            console.log(data);

            $('#output').append(JSON.stringify(data, null, 4) + "\n"); 
        });

    
    $('#go').on('click', ()=>{
        const message=$('#message').val();

        fetch('/write', {
            method: 'POST',
            body:JSON.stringify({
                message: message,
            })
        })
            .then((response)=>response.json())
            .then((data)=>{
                console.log(data);

                $('#output').append(JSON.stringify(data, null, 4) + "\n"); 
            });
    });

    

});