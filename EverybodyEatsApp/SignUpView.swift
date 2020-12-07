//
//  SignUpView.swift
//  FirebaseLogin
//


import SwiftUI
import Firebase
import Foundation
import CoreLocation

struct actIndSignup: UIViewRepresentable {
    @Binding var shouldAnimate: Bool
    
    func makeUIView(context: Context) -> UIActivityIndicatorView {
        return UIActivityIndicatorView()
    }
    
    func updateUIView(_ uiView: UIActivityIndicatorView,
                      context: Context) {
        if self.shouldAnimate {
            uiView.startAnimating()
        } else {
            uiView.stopAnimating()
        }
    }
}
struct SignUpView: View {
    
    @Environment(\.presentationMode) var presentationMode
    @State var emailAddress: String = ""
    @State var password: String = ""
    @State var first_name: String = ""
    @State var last_name: String = ""
    @State var venmoID: String = ""
    @State var agreeCheck: Bool = false
    @State var errorText: String = ""
    @State private var showAlert = false
    @State private var shouldAnimate = false
    
    var alert: Alert {
        
        Alert(title: Text("Verify your Email ID"), message: Text("Please click the link in the verification email sent to you"), dismissButton: .default(Text("Dismiss")){
            
            self.presentationMode.wrappedValue.dismiss()
            self.emailAddress = ""
            self.password = ""
            self.first_name = ""
            self.last_name = ""
            self.venmoID = ""
            self.agreeCheck = false
            self.errorText = ""
            
        })
    }
    
    var body: some View {
        
        VStack {
            
            //AppTitleView(Title: "Sign Up")
                        
            VStack(spacing: 5) {
                
                Image("words").padding(.top,45).padding(.bottom,45)
                Group{
                    Text("Email").font(.title).fontWeight(.thin).frame(minWidth: 0, maxWidth: .infinity, alignment: .topLeading).autocapitalization(.none)
                    TextField("username@umbc.edu", text: $emailAddress).textContentType(.emailAddress).autocapitalization(.none)
                    
                    Text("First Name").font(.title).fontWeight(.thin)
                        .frame(minWidth: 0, maxWidth: .infinity, alignment: .topLeading)
                    TextField("Enter your First Name", text: $first_name)
                    
                    Text("Last Name").font(.title).fontWeight(.thin)
                        .frame(minWidth: 0, maxWidth: .infinity, alignment: .topLeading)
                    TextField("Enter your Last Name", text: $last_name)
                    
                    Text("Venmo ID").font(.title).fontWeight(.thin)
                        .frame(minWidth: 0, maxWidth: .infinity, alignment: .topLeading)
                    TextField("Enter your Venmo ID", text: $venmoID)
                    
                    Text("Password").font(.title).fontWeight(.thin)
                        .frame(minWidth: 0, maxWidth: .infinity, alignment: .topLeading)
                    SecureField("Enter a password", text: $password)
                }
                
                
                
                Toggle(isOn: $agreeCheck)
                {
                    Text("Agree to the Terms and Condition").fontWeight(.thin)
                    
                }.frame(minWidth: 0, maxWidth: .infinity, alignment: .topLeading)
                
                Button(action: {
                    
                    if(self.agreeCheck){
                        print("Printing outputs" + self.emailAddress, self.password  )
                        self.shouldAnimate = true
                        self.sayHelloWorld(email:self.emailAddress, password:self.password)
                    }
                    else{
                        self.errorText = "Please Agree to the Terms and Condition"
                    }
                }) {
                    
                    Text("Sign Up")
                    
                }
                
                Text(errorText).frame(minWidth: 0, maxWidth: .infinity, alignment: .topLeading)
                
                actIndSignup(shouldAnimate: self.$shouldAnimate)
                
                
            }.padding(10)
            
        }.edgesIgnoringSafeArea(.top).frame(minWidth: 0, maxWidth: .infinity, minHeight: 0, maxHeight: .infinity, alignment: .topLeading).background(Color.white)
        
        
        .alert(isPresented: $showAlert, content: { self.alert })
        
    }
    
    
    func sayHelloWorld(email: String, password: String) {
        
        
        Auth.auth().createUser(withEmail: email, password: password) { authResult, error in
            
            guard let user = authResult?.user, error == nil else {
                
                let errorText: String  = error?.localizedDescription ?? "unknown error"
                self.errorText = errorText
                
                return
            }
            
            Auth.auth().currentUser?.sendEmailVerification { (error) in
                if let error = error {
                    self.errorText = error.localizedDescription
                    return
                }
                self.showAlert.toggle()
                
                self.shouldAnimate = false
                
            }
            
            print("\(user.email!) created")
            sendUserData(uid: Auth.auth().currentUser!.uid)
        }
        
        
    }
    
    func sendUserData(uid: String){
        let db = Firestore.firestore()
        db.collection("users").addDocument(data: ["email": emailAddress,"id" : uid, "first_name": first_name, "last_name": last_name, "ratingsTotal": 0, "ratingAvg":0,"venmoID" : venmoID])
    }
}

struct SignUpView_Previews: PreviewProvider {
    static var previews: some View {
        SignUpView()
    }
}
