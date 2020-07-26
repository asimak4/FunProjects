import React, { Component } from 'react';
import { Tabs, Tab, Grid, Cell, List, ListItem, ListItemContent } from 'react-mdl';


class Projects extends Component {
  constructor(props) {
    super(props);
    this.state = { activeTab: 0 };
  }

  toggleCategories() {

    if(this.state.activeTab === 0){
      return(
        <div className = "projects-grid">
          <List>
                <ListItem>
                  <ListItemContent style={{fontSize: '30px', fontFamily: 'Courier New'}}>
                  Car Scraping Project
                  </ListItemContent>
                  <p>Developed a web scraper that automatically scraped a website, (Cars.com) using the BeautifulSoup Library to filter out
                   specific car requirements. It would then update the csv file and then send an email with new updated cars, which made the
                   selection process much more convenient and time efficient. (Python, BeautifulSoup,csvRequests)</p>
                </ListItem> 


                <ListItem>
                <ListItemContent style={{fontSize: '30px', fontFamily: 'Courier New',color: '#fd1d1d'}}>
                <i className="fa fa-code" aria-hidden="true"/>  
                </ListItemContent>
                </ListItem>
                
                <ListItem>
                <ListItemContent style={{fontSize: '30px', fontFamily: 'Courier New'}}>
                Stock Predictor
                </ListItemContent>
                <p>Basic model which inputs any stocks data selected by the user, using panda’s library in python, 
                 taking 10 years of data (or as long as the stock as has been around) and builds and trains a model to 
                  estimate an advanced price for that specified stock. Representing that data as a graph for the actual plot vs 
                expected future plot. (Python,Pandas,MatPlot)</p>
                
                
                </ListItem>

                <ListItem>
                <ListItemContent style={{fontSize: '30px', fontFamily: 'Anton', color: '#fd1d1d'}}>
                <i className="fa fa-terminal" aria-hidden="true"/>  
                </ListItemContent>
                </ListItem>

                <ListItem>
                <ListItemContent style={{fontSize: '30px', fontFamily: 'Courier New'}}>
                Database Management Systems
                </ListItemContent>
                <p>Worked with a team to develop a database of the faculty members at the university and were able to 
                  link the schema to a query language (SQL) using Python to access, update and administer the SQL tables created. 
                  Developed a minimal user interface using python that would let the user easily and functionally be able to access the data. (Python, SQL)</p>
                </ListItem>
                
                <ListItem>
                <ListItemContent style={{fontSize: '30px', fontFamily: 'Anton', color: '#fd1d1d'}}>
                <i className="fa fa-code-fork" aria-hidden="true"/>  
                </ListItemContent>
                </ListItem>

                <p>Others not listed.</p>
          </List>
        </div>


      )
    } else if(this.state.activeTab === 1) {
      return (
        <div className="projects-grid">
          <List>
          <ListItem>
            <ListItemContent style={{fontSize: '30px', fontFamily: 'Courier New'}}>
            MERN with AWS
            </ListItemContent>
            <p>
            Created a simple website using HTML/CSS and ReactJS framework. 
            The website took in user input (login information) and was able to link the 
            information with the database which either allowed or denied user permission to the application. 
            Afterwards, linking the website to an AWS EC2 instance to maintain and publish the website. 
            (HTML, CSS, REACTJS, EC2, MangoDB, ExpressJS, NodeJS)
            </p>

          </ListItem>

          <ListItem>
          <ListItemContent style={{fontSize: '30px', fontFamily: 'Anton', color: '#fd1d1d'}}>
            <i className="fa fa-code-fork" aria-hidden="true"/> 
          </ListItemContent>
          </ListItem>

          <ListItem>
            <ListItemContent style={{fontSize: '30px', fontFamily: 'Courier New'}}>
            Online Portfolio (This Website)
            </ListItemContent>
            <p>
            Developed this simple website using HTML/CSS and ReactJS/NodeJS framework. 
            Using only basic CSS/HTML, without any preloaded libraries, Built to show my projects and experience levels, a bit about me 
            and a way to contact me to get to know me better! :) 
            </p>

          </ListItem>

          <ListItem>
          <ListItemContent style={{fontSize: '30px', fontFamily: 'Anton', color: '#fd1d1d'}}>
            <i className="fa fa-code" aria-hidden="true"/> 
          </ListItemContent>
          </ListItem>

          </List>
        </div>
      )
    } else if(this.state.activeTab === 2) {
      return (
        <div className="projects-grid">
        <List>
          <ListItem>
            <ListItemContent style={{fontSize: '30px', fontFamily: 'Courier New'}}>
            MERN with AWS
            </ListItemContent>
            <p>
            Created a simple website using HTML/CSS and ReactJS framework. 
            The website took in user input (login information) and was able to link the 
            information with the database which either allowed or denied user permission to the application. 
            Afterwards, linking the website to an AWS EC2 instance to maintain and publish the website. 
            (HTML, CSS, REACTJS, EC2, MangoDB, ExpressJS, NodeJS)
            </p>

          </ListItem>

          <ListItem>
          <ListItemContent style={{fontSize: '30px', fontFamily: 'Anton', color: '#fd1d1d'}}>
            <i className="fa fa-code-fork" aria-hidden="true"/> 
          </ListItemContent>
          </ListItem>

          <ListItem>
            <ListItemContent style={{fontSize: '30px', fontFamily: 'Courier New'}}>
            Online Portfolio (This Website)
            </ListItemContent>
            <p>
            Developed this simple website using HTML/CSS and ReactJS/NodeJS framework. 
            Using only basic CSS/HTML, without any preloaded libraries, Built to show my projects and experience levels, a bit about me 
            and a way to contact me to get to know me better! :) 
            </p>

          </ListItem>

          <ListItem>
          <ListItemContent style={{fontSize: '30px', fontFamily: 'Anton', color: '#fd1d1d'}}>
            <i className="fa fa-code" aria-hidden="true"/> 
          </ListItemContent>
          </ListItem>

          </List>
          </div>
      )
    }

  }



  render() {
    return(
      <div>
        <Tabs activeTab={this.state.activeTab} onChange={(tabId) => this.setState({ activeTab: tabId })} ripple>
          <Tab>Python</Tab>
          <Tab>Javascript/React</Tab>
          <Tab>C++</Tab>
        </Tabs>


          <Grid>
            <Cell col={12}>
              <div className="content">{this.toggleCategories()}</div>
            </Cell>
          </Grid>


      </div>
    )
  }
}

export default Projects;
