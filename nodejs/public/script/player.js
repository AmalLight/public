
function buildQuestion( titolo ) {
    var question = function_json.question( titolo );

    $( "#questionParagraph" ).html(
        `<h1 class="lead text-muted" id="questionParagraph"> ${question.Domanda} </h1>
         <h2 class="lead text-muted" >Numero domanda : ${function_json.readps(titolo)+1} </h2>` );

    $( "#answerButtons" ).html(

        `<button type="submit" onclick="submitAnswer('${titolo}', 1)" class="btn btn-secondary btn-lg btn-block" id="answer1">
             ${question.Risposta1}
         </button>
         <button type="submit" onclick="submitAnswer('${titolo}', 2)" class="btn btn-secondary btn-lg btn-block" id="answer2">
             ${question.Risposta2}
         </button>
         <button type="submit" onclick="submitAnswer('${titolo}', 3)" class="btn btn-secondary btn-lg btn-block" id="answer3">
             ${question.Risposta3}
         </button>
         <button type="submit" onclick="submitAnswer('${titolo}', 4)" class="btn btn-secondary btn-lg btn-block" id="answer4">
             ${question.Risposta4}
        </button>`
    );
}

// funzione che carica la schermata di gioco
function loadGame( titolo )
{
    function_json.selTitolo( titolo );
    function_json.selText( '' );

    $( "#home" ).hide();
    $( "#storiesJumbotron" ).hide();
    $( "#questionsJumbotron" ).show(); 
    $( "#answerButtons" ).show();

    buildQuestion( titolo );
}

function loadStories() {
    $( "#home" ).hide();
    $( "#software" ).hide();
    $( "#answerButtons" ).hide();
    $( "#questionsJumbotron" ).hide();

    $( "#storiesJumbotron" ).show();
    $( "#footer" ).hide();
}

//funzione che carica la schermata di risposta alla domanda
function submitAnswer( titolo, numero ) {
    var question = function_json.question( titolo );

    function_json.selText( question[ ( 'Risposta' + String(numero) ) ] );

    var TextSelected = function_json.readText();

    $("#answerParagraph").replaceWith('<h2 class="lead text-muted" id="answerParagraph">' + TextSelected + '</h2>');
    $("#answerButtons").hide(); 
    $("#answerSubmission").show();
    $("#answerParagraph").show();
}

function backtoQuestion ( titolo )
{
    $("#answerButtons").show();
    $("#answerSubmission").hide();
    $("#answerParagraph").hide();

    buildQuestion( titolo );
}

function confirmAnswer() {
    var TitoloSelected = function_json.readTitolo();
    var TextSelected   = function_json.readText();
    var Textright      = function_json.question( TitoloSelected ).Risposta5;

    if ( TextSelected == Textright )
    {
        function_json.nextps( TitoloSelected );

        $("#answerButtons").show();
        $("#answerSubmission").hide();
        $("#answerParagraph").hide();

        buildQuestion( TitoloSelected );
    }

    else
    {
        $('#wrongAnswer').show();
        $("#answerSubmission").hide();

        $('#closeAlert').click(function(){ backtoQuestion( TitoloSelected ); });
    }
}
