import java.io.*;
import java.util.*;

public class Main {
	
	public static ArrayList<Graph> shortestPath = new ArrayList<Graph>();
	
	public static void main(String[] args){
		
		ArrayList<Graph> allWord = new ArrayList<Graph>();		
		ArrayList<Graph> path = new ArrayList<Graph>();		/* define to assign shortestPath return findSortestPath method */
		
		String dictionaryLine = null;
		String inputLine = null;
		String inputLineNumber = null;
		
		String dictionaryFileName = args[0];
		String inputFileName = args[1];
		String inputLineNumberFileName = args[1];
		String outputFileName = args[2];
		
		BufferedReader dictionaryBufferedReader = null;
		BufferedReader inputBufferedReader = null;
		BufferedReader inputLineNumberBufferedReader = null;
		BufferedWriter outputBufferedWriter = null;
		
			
		try{	/* read dicitonary file try block */
			
			FileReader dictionaryFileReader = new FileReader(dictionaryFileName);		/* open to read dictionary file */
			dictionaryBufferedReader = new BufferedReader(dictionaryFileReader);
			
			while((dictionaryLine = dictionaryBufferedReader.readLine()) != null){
				Graph newGraph = new Graph(dictionaryLine);			/* create new graph node for every word */
				allWord.add(newGraph);		/* every word add allWord array list */
			}
			
			addNeighbors(allWord);		/*call addNeighbor function for build neighbor's relationship all word */
			
			try{		/* read input file try block */
			
				FileReader inputFileReader = new FileReader(inputFileName);		/* open to read input file */
				inputBufferedReader = new BufferedReader(inputFileReader);
				
				FileReader inputLineNumberReader = new FileReader(inputLineNumberFileName);		/* open to learn input line number */
				inputLineNumberBufferedReader = new BufferedReader(inputLineNumberReader);
				
				int numberOfLİne = 0;
				while( (inputLineNumber = inputLineNumberBufferedReader.readLine()) != null ){	/* assign numberOfLİne that input line number */
					numberOfLİne++;
				}
				
				try{	/* write output file try block */
					
					FileWriter outputFileWriter = new FileWriter(outputFileName);		/* open to write output file */
					outputBufferedWriter = new BufferedWriter(outputFileWriter);
					
					int counter = 0; /*  */
					while( (inputLine = inputBufferedReader.readLine()) != null ){
					
						counter++;		/* bu sayac inputun son satirini isledikten sonra yeni satira gecmemek icin */
						
						String[] startAndEndWord = inputLine.split(" ");	/* split input line and assign start and end word */
						String startWord = startAndEndWord[0];
						String endWord = startAndEndWord[1];
						
						if(wordExistControl(startWord,endWord,allWord)){	/* control start and end word exist in dictionary */
																			/* if exist words call findShortest method and assign path */
							path = findShortestPath(allWord,startWord,endWord,outputBufferedWriter);
							
							if(path != null){	/* if least path exist */
								
								for(Graph v : path){	/* for each graph node */
									
									outputBufferedWriter.write(v.word);		/* print path */
									
									if(!v.word.equals(endWord)){
										outputBufferedWriter.write(",");
									}
									
								}
								
								if(counter != numberOfLİne)
									outputBufferedWriter.newLine();
								
								path.clear();	/* clear path for use again */
								
							}else{		/* if any path does not exist start word from end word  */
								
								outputBufferedWriter.write("Failure");		/* print failure message */
								if(counter != numberOfLİne)
									outputBufferedWriter.newLine();
								
							}
							
						}else{		/* if words don't exist in dictionary */
							
							outputBufferedWriter.write("Failure");		/* print failure message */
							if(counter != numberOfLİne)
									outputBufferedWriter.newLine();
							
						}
						
					}
					
				}catch(IOException ex){		/* output file catch block */
				
					System.out.println("Error writing file '" + outputFileName + "'");
					
				}finally{		/* output file finally block */
				
					try{		/* close output file try block */
					
						if(outputBufferedWriter != null){
							outputBufferedWriter.close();
						}

					}catch(IOException e){		/* close output file catch block */
					
						System.out.println("Error close '" + outputFileName + "'");
						
					}
					
				}
				
			}catch(IOException ex){		/* read input file catch block */
			
				System.out.println("Error reading file '" + inputFileName + "'");
				
			}finally{		/* input file finally block */
			
				try{		/* close input file try block */
				
					if(inputBufferedReader != null){
						inputBufferedReader.close();
					}

				}catch(IOException e){		/* close input file catch block */
				
					System.out.println("Error close '" + inputFileName + "'");
					
				}
				
			}

		}catch(IOException ex){		/* read dictionary file catch block*/
		
			System.out.println("Error reading file '" + dictionaryFileName + "'");
			
		}finally{		/* dictionary file finally block */
			
			try{		/* close dictionary file try block */
			
				if(dictionaryBufferedReader != null){
					dictionaryBufferedReader.close();
				}
				
			}catch(IOException e){		/* close dictionary file catch block */
			
				System.out.println("Error close '" + dictionaryFileName + "'");
				
			}
			
		}/* end finally block */
		
	}/* end main method */
	
	public static void addNeighbors(ArrayList<Graph> allWords){		/* this method add all word's neighbors */
		
		for(Graph graph : allWords){
			for(Graph graph2 : allWords){
				if( !graph.word.equals(graph2.word) ){
				
					boolean control = false;
					char[] word1 = graph.word.toCharArray();
					char[] word2 = graph2.word.toCharArray();
					
					for(int i=0; i<graph.word.length(); i++){	/* control neighbor */
						
						if(word1[i] != word2[i]){
							
							for(int j=0; j<graph.word.length(); j++){
							
								if(i!=j){
								
									if(word1[j]==word2[j]){
										control = true;
									}
									
									else{
										control = false;
										break;
									}
									
								}
								
							}
							
							break;
						}
						
					}
					
					if(control == true){	/* if graph2 node is neighbor grpah1 node, add neighbor */
						graph.neighbors.add(graph2);
					}
					
				}
			}
		}
		
	}/* end addNeighbor method */
	
	
	public static boolean wordExistControl(String startWord, String endWord, ArrayList<Graph> allWords){	/* this method control start and end words exist in dictionary */
		
		boolean control1 = false;
		boolean control2 = false;
		
		for(Graph v : allWords){		/* start word control */
			if(v.word.equals(startWord)){
				control1 = true;
				break;
			}
		}
		for(Graph v : allWords){		/* end word control */
			if(v.word.equals(endWord)){
				control2 = true;
				break;
			}
		}
		
		if(control1 && control2)	/* if words exist return true */
			return true;
		else
			return false;
		
	}
	
	/* this method Breath First Search algorithm */
	public static ArrayList<Graph> findShortestPath(ArrayList<Graph> allWords, String startWord, String endWord, BufferedWriter outputBufferedWriter ){
		
		ArrayList<Graph> queue = new ArrayList<Graph>();
		ArrayList<Graph> path = new ArrayList<Graph>();
		ArrayList<Graph> visited = new ArrayList<Graph>();
		
		Graph started = null;
		Graph ended = null;
		
		for(Graph graph : allWords){	/* find start and end node in graph */
		
			if(graph.word.equals(startWord)){
				started = graph;
			}
			if(graph.word.equals(endWord)){
				ended = graph;
			}
			
		}
		
		if(startWord.equals(endWord)){		/* if start word is equal end word return itself */
		path.add(started);
			return path;
		}
		
		queue.add(started);				/* BFS algorithm */
		
		while(!queue.isEmpty()){

			Graph vertex = queue.get(0);
			queue.remove(0);
			visited.add(vertex);
			
			int index = 0;
			int neighborsSize = vertex.neighbors.size();
			
			while(index != neighborsSize){	/*node's all neighbor come from queue */

				Graph neighbor = vertex.neighbors.get(index);
				
				path.add(neighbor);
				path.add(vertex);
				
				if(neighbor.word.equals(endWord)){
					return processPath(started,ended,path);
				}
				else{
					if(!visited.contains(neighbor)){
						queue.add(neighbor);
					}
				}
				
				index++;
				
			}
			
		}/* end while loop */
		
		return null;
		
	}
	
	/* this method is recursive function */
	public static ArrayList<Graph> processPath(Graph started, Graph ended, ArrayList<Graph> path){
	
		int index = path.indexOf(ended);
		Graph start = path.get(index+1);
		shortestPath.add(0,ended);
		
		if(start.word.equals(started.word)){
			shortestPath.add(0,started);
			return shortestPath;	/* return shortest path */
		}else{
			return processPath(started,start,path);		/* call processPath method */
		}
		
	}
	
}