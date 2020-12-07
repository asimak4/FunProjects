//
//  WelcomeView.swift
//  FirebaseLogin
//


import SwiftUI
import Firebase

public var screenWidth: CGFloat {
     return UIScreen.main.bounds.width
 }
public var screenHeight: CGFloat {
    return UIScreen.main.bounds.height
}

struct WelcomeView: View {
  
       @State var signUpIsPresent: Bool = false
       @State var signInIsPresent: Bool = false
       @State var selection: Int? = nil
       @State var viewState = CGSize.zero
       @State var MainviewState =  CGSize.zero
       
       var body: some View {
        
        ZStack{
            
           if Auth.auth().currentUser != nil {
             VStack{
                     /*
                     AppTitleView(Title: "Home")
                     Spacer()
                     Text("Hello World!")
                    */
                     NavigationView{
                        ContentView()
                            .navigationBarHidden(true)
                            .navigationBarBackButtonHidden(true)
                     }
                     Spacer()

                     }.edgesIgnoringSafeArea(.top).background(Color.white)
                      .offset(x: self.MainviewState.width).animation(.spring())
            }
            
           else {
            
            VStack {
                              
                           
                        //AppTitleView(Title: "Welcome")
                        //Spacer()
                        VStack(spacing:20) {
                            Spacer(minLength: 0.5)
                            Image("word_with_car").resizable().scaledToFit()
                            Spacer()
                            Button(action: {self.signUpIsPresent = true}){
                                Text("Sign Up")
                                  
                            }.sheet(isPresented: self.$signUpIsPresent){
                                    
                                  SignUpView()
                                  
                            }
                                
                            Button(action: {self.signInIsPresent = true}){
                                  
                                Text("Sign In")
                            }.sheet(isPresented: $signInIsPresent) {
                                  
                                  SignInView(onDismiss:{
                                      
                                  self.viewState = CGSize(width: screenWidth, height: 0)
                                  self.MainviewState = CGSize(width: 0, height: 0)
                                      
                                  })};Spacer();}
                        Spacer()
                              
                }.edgesIgnoringSafeArea(.top).edgesIgnoringSafeArea(.bottom)
                .offset(x:self.viewState.width).animation(.spring())
            }

        }
       
   }
    
}



struct WelcomeView_Previews: PreviewProvider {
    static var previews: some View {
        WelcomeView()
    }
}

