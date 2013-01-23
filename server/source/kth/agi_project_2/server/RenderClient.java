/**
 * Handles communication with a render client.
 * @author Eric Nellåker
 */

package kth.agi_project_2.server;

import java.io.IOException;
import java.io.OutputStream;
import java.net.Socket;
import java.util.ListIterator;

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
	
	private Socket soc;
	private OutputStream os;
	private GameState gs;
	
	public RenderClient(Socket soc, GameState gs) throws IOException
	{
		this.soc = soc;
		this.gs = gs;
		os = soc.getOutputStream();		
	}

	public boolean isOpen()
	{
		return !soc.isClosed();
	}
	public void send()
	{
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
			ListIterator<Airplane> aIt = gs.getPlaneIterator();
			Entity temp;
			while(aIt.hasNext())
			{
				temp = aIt.next();
				Element p = doc.createElement("p");
				planes.appendChild(p);
				Attr id = doc.createAttribute("id");
				id.setValue(""+temp.getId());
				p.setAttributeNode(id);

				Element x = doc.createElement("x");
				x.appendChild(doc.createTextNode(""+temp.getPos().x));
				p.appendChild(x);

				Element y = doc.createElement("y");
				y.appendChild(doc.createTextNode(""+temp.getPos().y));
				p.appendChild(y);

				Element a = doc.createElement("a");
				a.appendChild(doc.createTextNode(""+temp.getAngle()));
				p.appendChild(a);

				Element status = doc.createElement("status");
				status.appendChild(doc.createTextNode(""+temp.getStatus()));
				p.appendChild(status);
			}
			Element bullets = doc.createElement("bullets");
			rootElement.appendChild(bullets);
			ListIterator<Bullet> bIt = gs.getBulletIterator();
			while(bIt.hasNext())
			{
				temp = bIt.next();
				Element b = doc.createElement("b");
				bullets.appendChild(b);
				Attr id = doc.createAttribute("id");
				id.setValue(""+temp.getId());
				b.setAttributeNode(id);
				
				Element x = doc.createElement("x");
				x.appendChild(doc.createTextNode(""+temp.getPos().x));
				b.appendChild(x);

				Element y = doc.createElement("y");
				y.appendChild(doc.createTextNode(""+temp.getPos().y));
				b.appendChild(y);

				Element a = doc.createElement("a");
				a.appendChild(doc.createTextNode(""+temp.getAngle()));
				b.appendChild(a);

				Element status = doc.createElement("status");
				status.appendChild(doc.createTextNode(""+temp.getStatus()));
				b.appendChild(status);
			}
			TransformerFactory transformerFactory = TransformerFactory.newInstance();
			Transformer transformer = transformerFactory.newTransformer();
			DOMSource source = new DOMSource(doc);
			
			StreamResult result = new StreamResult(os);
			transformer.transform(source,result);
			os.write("\n".getBytes());
			os.flush();
		}
		catch (ParserConfigurationException pce) {
			System.err.println("Parser exception! Did a renderer disconnect?");
			try {
				soc.close();
				return;
			} catch (IOException e) {
				
				System.err.println("... and an IOException to boot!");
				return;
			}
		} catch (TransformerException tfe) {
			System.err.println("Transformer Exception! Did a renderer disconnect?");
			try {
				soc.close();
				return;
			} catch (IOException e) {
				System.err.println("... and an IOException to boot!");
				return;
			}
		} catch (IOException e) {
			System.err.println("IO Exception! Did a renderer disconnect?");
			try {
				soc.close();
				return;
			} catch (IOException e1) {
				System.err.println("... and an IOException to boot!");
				return;
			}
		} 
	}
	
	public Socket getSocket()
	{
		return soc;
	}
}
