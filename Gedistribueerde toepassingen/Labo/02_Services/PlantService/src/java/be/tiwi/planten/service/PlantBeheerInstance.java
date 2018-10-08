package be.tiwi.planten.service;

import be.tiwi.planten.impl.PlantenGeheugenDB;
import java.io.IOException;
import java.nio.file.FileSystems;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.stream.Stream;


public class PlantBeheerInstance {
    private static PlantenGeheugenDB pb;
    
    public static PlantenGeheugenDB GetInstance() throws IOException{
        if(pb == null){
            Path path = FileSystems.getDefault().getPath("", "planten.txt");
            Stream<String> stream = Files.lines(path);
            stream.forEach((s) -> {
                s.split(";")
                        //TODO; inlezen
                
            });
            pb = new PlantenGeheugenDB();
        }
        return pb;
    }
}
