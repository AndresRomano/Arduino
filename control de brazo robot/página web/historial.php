<!DOCTYPE html>
<html>
<p>
        <A href="paginaPrincipal.html" plain> Volver a la pagina principal </A> 
</p>
</html>

<?php
  
  
echo nl2br (file_get_contents("historial.info","r"));

?>