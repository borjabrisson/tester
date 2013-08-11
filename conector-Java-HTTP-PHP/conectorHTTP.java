//Libreria para Streams de lectura y escritura
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLConnection;
import java.net.URLEncoder;

import java.text.ParseException;
import java.util.Iterator;
import java.util.LinkedHashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

import org.json.simple.JSONValue;
import org.json.simple.parser.ContainerFactory;
import org.json.simple.parser.JSONParser;
//import org.apache.http.NameValuePair;

//Libreria para conexión URLConnection
//https://code.google.com/p/json-simple/wiki/DecodingExamples

public class conectorHTTP {

	/**
	 * @param args
	 */
	/*public static void main(String[] args) {
		// TODO Auto-generated method stub

	}*/
	public static void main(String[] args)
		throws MalformedURLException, IOException, ParseException {

        /*
           Creo un objeto de tipo url, con la dirección URL
           y el archivo que sera procesado en el servidor
           En este ejemplo el archivo es http.php
           y vive en un servidor local.
         */

	    URL url = new URL("http://localhost/http.php");

          //Abro la conexión

	    URLConnection con = url.openConnection();

          //Permito el envío de mensajes hacia ese servidor
	    con.setDoOutput(true);

          /*
             Establezco y codifico en POST lo que se enviará
             dato1=123&dato2=456
          */

	    String data =""+
	    URLEncoder.encode("dato1", "UTF-8") + "=" +
				 URLEncoder.encode("peeeeee", "UTF-8");

	    data += "&" + URLEncoder.encode("dato2", "UTF-8") +
				"=" + URLEncoder.encode("peeeee", "UTF-8");

          /*
             Creo un stream de salida para el envío de estos datos
             usando la conexión URL
          */
	    OutputStreamWriter wr =
			new OutputStreamWriter(con.getOutputStream());

          //Escribo en el stream de salida ...osea se van los datos
	    wr.write(data);

          //Libero el stream de salida una vez enviado todo
	    wr.flush();

          /*
             Creo un stream de entrada, mediante el cual
             veré que respondió el servidor de acuerdo a los datos
             que le envié, de igual manera usando la conexión URL
          */
	    BufferedReader in = new BufferedReader(
	    		new InputStreamReader(con.getInputStream()));

          /*
             Leo todo el contenido recibido hasta que sea nulo
             esto se hace linea por linea y se guarda en una variable,
             por eso se usa el ciclo while.
          */
	 /*   String linea;

	    while ((linea = in.readLine()) != null) {
	         System.out.println(linea);
	    }*/
	    
	    StringBuilder sb = new StringBuilder();
        String line = null;
        while ((line = in.readLine()) != null) {
            sb.append(line + "\n");
        }
        System.out.println(sb.toString());
        //JSONObject json = sb.toString();
        
        
       
        String jsonText = sb.toString();//"{\"first\": 123, \"second\": [4, 5, 6], \"third\": 789}";
        JSONParser parser = new JSONParser();
        ContainerFactory containerFactory = new ContainerFactory(){
        	public List creatArrayContainer() {
        		return new LinkedList();
        	}

        	public Map createObjectContainer() {
        		return new LinkedHashMap();
        	}

        };

        Map json = null;
		try {
			json = (Map)parser.parse(jsonText, containerFactory);
		} catch (org.json.simple.parser.ParseException e) {
			// TODO Auto-generated catch block
			System.out.println("==Fallo de parser==");
			e.printStackTrace();
		}
		Iterator iter = json.entrySet().iterator();
		System.out.println("==iterate result==");
		while(iter.hasNext()){
			Map.Entry entry = (Map.Entry)iter.next();
			System.out.println(entry.getKey() + "=>" + entry.getValue());
		}

		System.out.println("==toJSONString()==");
		System.out.println(JSONValue.toJSONString(json));
         
	}

}
