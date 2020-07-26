import React, { Component } from 'react';
import { Grid, Cell } from 'react-mdl';
import Education from './education';
import Experience from './experience';
import Skills from './skills';


class Resume extends Component {
  render() {
    return(
      <div>
        <Grid>
          <Cell col={4}>
            <div style={{textAlign: 'center'}}>
              <img
                src="https://www.clipartkey.com/mpngs/m/279-2795926_recruit-resume-school-icon-for-resume.png"
                alt="avatar"
                style={{height: '150px'}}
                 />
            </div>

            <h2 style={{paddingTop: '2em'}}>Alexander D Simak</h2>
            <h4 style={{color: 'grey'}}>Programmer/Student</h4>
            <hr style={{borderTop: '3px solid #833fb2', width: '50%'}}/>
            <h5>Phone</h5>
            <p>(443) 474 0722 </p>
            <h5>Email</h5>
            <p>asimak4@gmail.com</p>
            <hr style={{borderTop: '3px solid #833fb2', width: '50%'}}/>
          </Cell>
          <Cell className="resume-right-col" col={8}>
            <h2>Education</h2>


            <Education
              startYear={2017}
              endYear={2021}
              schoolName="University of Maryland, Baltimore County"
              schoolDescription="Bachelor's Degree in Computer Science with a Mathematics Minor GPA: 3.7"
              />

               <Education
                 startYear={2014}
                 endYear={2017}
                 schoolName="Mount Hebron High School"
                 schoolDescription="General Studies High School Diploma GPA: 3.87"
                  />
                <hr style={{borderTop: '3px solid #e22947'}} />

              <h2>Experience</h2>

            <Experience
              startYear={2019}

              jobName="Battelle Memorial Institute - IT Intern"
              jobDescription="
              Testing Software Applications and business systems,
              Troubleshooting Computer Hardware related problems such as UPS, Printers and Drivers,
              Managing and maintaining Servers, PC’S Routers and Switches,
              Installing, configuring and administering network technologies,
              Backup management, reporting and recovery"
              />

              <Experience
                startYear={2017}
                jobName="ICFX Technologies - Cell Phone Technician"
                jobDescription="Answering customer inquiries regarding cell phone software and hardware operations, 
                Installing and repairing cell phone/computer hardware, software, and peripheral equipment, 
                following design or installation specifications, 
                Developing training procedures and training users in the proper use of hardware and software"
                />
              
              <Experience
                startYear={2016}
                endYear={2017}
                jobName="Johns Hopkins Applied Physics Lab - Intern"
                jobDescription="Built a graphing calculator using reverse polish notation in the C programming language,
                Designed and developed a basic checkers game with a graphical user interface, implemented
                in the C programming language"
                />
              <hr style={{borderTop: '3px solid #e22947'}} />
              <h2>Skills</h2>
              <Skills
                skill="Python"
                progress={99}
              />
              <Skills
                  skill="C++"
                  progress={80}
              />
              <Skills
                skill="CSS/HTML"
                progress={70}
                />
              <Skills
                skill="Javascript"
                progress={60}
              />
              
              <Skills
                skill="React/NodeJS"
                progress={30}
                />


          </Cell>
        </Grid>
      </div>
    )
  }
}

export default Resume;
