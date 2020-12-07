//
//  ChatView.swift
//  ErryBody Eats
//
//  Created by Ashar Nadeem on 11/24/20.
//

import SwiftUI
import Firebase

struct ChatView: View {
    
    @ObservedObject var homeData: HomeViewModel
    var driver_id: String
    @State var text: String = ""

    var body: some View {
        
        VStack(spacing: 10){
        
            HStack(spacing: 20){
                NavigationLink(destination: CartView(homeData: homeData)){
                    Image(systemName: "chevron.left")
                        .font(.system(size: 26, weight: .heavy))
                        .foregroundColor(Color("pink"))
                }
                
                Text("Chat")
                    .font(.title)
                    .fontWeight(.heavy)
                    .foregroundColor(.black)
                Spacer()
                
            }
            .padding()
                
            ScrollView() {
                VStack() {
                    ForEach(homeData.messages) { message in
                        if message.fromId == homeData.uid {
                            HStack() {
                                Spacer()
                                Text(message.message)
                                .padding(8)
                                .background(Color.pink)
                                .cornerRadius(2)
                                Spacer().frame(width: 7)
                            }
                        }
                        else{
                            HStack() {
                                Spacer().frame(width: 7)
                                Text(message.message)
                                .padding(8)
                                .background(Color.gray.opacity(0.25))
                                .cornerRadius(2)
                                Spacer()
                            }
                        }
                    }
                }.rotationEffect(.degrees(180))
            }.rotationEffect(.degrees(180))
            .onAppear(perform: {
                    getMessages()
                //print(delivery.driver_id)
                //print(homeData.uid)
            })
                    
            VStack() {
                Spacer()
                HStack {
                    TextField("Type a message", text: $text)
                    Button(action: {
                        homeData.sendMessage(toId: driver_id, message: text);
                        text = "";
                        getMessages()
                    }){ Text("Send") }.foregroundColor(Color.pink)
                }.padding()
            }.frame(height: 40)
        }
    }

    func getMessages(){
        homeData.messages.removeAll()
        homeData.getSentMessages(driverId: driver_id)
        homeData.getRecvMessages(driverId: driver_id)
    }
}
