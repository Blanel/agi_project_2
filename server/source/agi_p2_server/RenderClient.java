package agi_p2_server;

import java.io.File;
import java.io.IOException;
import java.net.Socket;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

import org.w3c.dom.Attr;
import org.w3c.dom.Document;
import org.w3c.dom.Element;

public class RenderClient {

	public void send(GameState gs)
	{
		Socket soc = new Socket();
		try
		{
			DocumentBuilderFactory docFactory = DocumentBuilderFactory.newInstance();
			DocumentBuilder docBuilder = docFactory.newDocumentBuilder();

			Document doc = docBuilder.newDocument();

			Element rootElement = doc.createElement("tick");
			doc.appendChild(rootElement);
			Attr ts = doc.createAttribute("ts");
			ts.setValue(""+System.currentTimeMillis());
			rootElement.setAttributeNode(ts);

			Element planes = doc.createElement("planes");
			rootElement.appendChild(planes);

			for(int i=0 ; i< gs.airplanes.size() ; i++)
			{
				Element p = doc.createElement("p");
				planes.appendChild(p);
				Attr id = doc.createAttribute("id");
				id.setValue(""+gs.airplanes.get(i).getId());
				p.setAttributeNode(id);

				Element x = doc.createElement("x");
				x.appendChild(doc.createTextNode(""+gs.airplanes.get(i).getX()));
				p.appendChild(x);

				Element y = doc.createElement("y");
				y.appendChild(doc.createTextNode(""+gs.airplanes.get(i).getY()));
				p.appendChild(y);

				Element a = doc.createElement("a");
				a.appendChild(doc.createTextNode(""+gs.airplanes.get(i).getAngle()));
				p.appendChild(a);

				Element status = doc.createElement("status");
				status.appendChild(doc.createTextNode(""+gs.airplanes.get(i).getStatus()));
				p.appendChild(status);
				if(gs.airplanes.get(i).getStatus()==1)
					gs.airplanes.get(i).setStatus(0);
				else if(gs.airplanes.get(i).getStatus() == -1)
				{
					gs.airplanes.remove(i);
					i--;
				}
			}
			Element bullets = doc.createElement("bullets");
			rootElement.appendChild(bullets);
			for(int i=0 ; i<gs.bullets.size(); i++)
			{
				Element b = doc.createElement("b");
				bullets.appendChild(b);
				Attr id = doc.createAttribute("id");
				id.setValue(""+gs.bullets.get(i).getId());
				b.setAttributeNode(id);
				
				Element x = doc.createElement("x");
				x.appendChild(doc.createTextNode(""+gs.bullets.get(i).getX()));
				b.appendChild(x);

				Element y = doc.createElement("y");
				y.appendChild(doc.createTextNode(""+gs.bullets.get(i).getY()));
				b.appendChild(y);

				Element a = doc.createElement("a");
				a.appendChild(doc.createTextNode(""+gs.bullets.get(i).getAngle()));
				b.appendChild(a);

				Element status = doc.createElement("status");
				status.appendChild(doc.createTextNode(""+gs.bullets.get(i).getStatus()));
				b.appendChild(status);
				if(gs.bullets.get(i).getStatus()==1)
					gs.bullets.get(i).setStatus(0);
				else if(gs.bullets.get(i).getStatus() < 0)
				{
					gs.bullets.remove(i);
					i--;
				}
			}
			TransformerFactory transformerFactory = TransformerFactory.newInstance();
			Transformer transformer = transformerFactory.newTransformer();
			DOMSource source = new DOMSource(doc);
			
			//StreamResult result = new StreamResult(soc.getOutputStream());
			StreamResult result = new StreamResult(System.out);
			transformer.transform(source,result);
		}
		catch (ParserConfigurationException pce) {
			pce.printStackTrace();
		} catch (TransformerException tfe) {
			tfe.printStackTrace();
		} 
	}

}
