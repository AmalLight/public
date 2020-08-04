function crea()
{
    $( '#home' ).hide();
    $( "#answerButtons" ).hide();
    $( '#storiesJumbotron' ).hide();
    $( "#questionsJumbotron" ).hide();

    $( '#software' ).show();
    $( '#footer'   ).hide();

    function_json.alloc( create_json_init() );
    function_json.reset();

    var text =
`
<div id=container2 class=col >
    Titolo              : <input    class="form-control noempty" type=text name=titolo >
    Descrizione         : <textarea class="form-control noempty" name=descrizione ></textarea>

    <div class='row text-right' >
        <div class=col-6 >
            <text>Checkbox per la Scuola!!</text><br><br>
            <text>elementari</text> <input type=radio name=scuola value=elementari checked ><br>
            <text>medie</text>      <input type=radio name=scuola value=medie ><br>
            <text>superiori</text>  <input type=radio name=scuola value=superiori ><br><br>
        </div>

        <div class=col-6 >
            <text>Checkbox per il Gruppo!!</text><br><br>
            <text>singolo</text> <input type=radio name=gruppo value=singolo checked ><br>
            <text>gruppo</text>  <input type=radio name=gruppo value=gruppo ><br>
            <text>classe</text>  <input type=radio name=gruppo value=classe >
        </div>
    </div>

    Nome creatore       : <input    class="form-control noempty" type=text name=nome    >
    Cognome creatore    : <input    class="form-control noempty" type=text name=cognome >
    Numero di Giocatori : <input    class="form-control noempty" type=text name=numero  >
</div>
`;
    $( '#riga3').html( text );
    
    text = 
    `
    <div class=col >
        Url Immagine o Video : <input class="form-control noempty" type=text name=url >

        <textarea class="form-control noempty" name=domanda >La Domanda</textarea>

        Risposta 1 : <input class="form-control noempty" type=text name=r1 >
        Risposta 2 : <input class="form-control noempty" type=text name=r2 >
        Risposta 3 : <input class="form-control noempty" type=text name=r3 >
        Risposta 4 : <input class="form-control noempty" type=text name=r4 >

        Risposta esatta : <input class="form-control noempty" type=text name=r5 >
    </div>
    `;
    
    $( '#riga4').html( text );
    
    text =

    `
    <div class="btn-group" role="group" id="editorButtonGroup" aria-label="Basic example" >

        <button type="button" class="btn btn-primary btn-lg" id=up onclick=up() > UP   </button >
        <button type="button" class="btn btn-primary btn-lg" id=dw onclick=dw() > DOWN </button >
        <button type="button" class="btn btn-primary btn-lg" onclick=plus()     > PLUS </button >
    </div>
    
    
    <div class="btn-group" role="group" id="editorButtonGroup" aria-label="Basic example" >

        <button type="button" class="btn btn-primary btn-lg" onclick=save()   > SAVE </button >
        <button type="button" class="btn btn-primary btn-lg" onclick=submit() > SEND </button >
    </div>   

    <div class='row text-center' >
        <text class=col >Domanda numero : <b id=domanda >0</b> .</text>
    </div> 
    `;
    
    $( '#riga2').html( text );   

    init_rige(); noempty();
}
