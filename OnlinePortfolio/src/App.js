import React, { Component } from 'react';
import './App.css';
import { Layout, Header, Navigation, Content,Drawer } from 'react-mdl';
import Main from './components/main';
import { HashRouter, Link } from 'react-router-dom';

class App extends Component {
  render() {
    return (
      <HashRouter>
      <div className="demo-big-content">
    <Layout>
        <Header className="header-color" title={<Link style={{textDecoration: 'none', color: 'black'}} to="/">Home</Link>} scroll>
        </Header>
        <Drawer title={<Link style={{textDecoration: 'none', color: 'black'}} to="/">Alex Simak Portfolio</Link>}>
            <Navigation>
              <Link to="/resume">Resume</Link>
              <Link to="/aboutme">About Me</Link>
              <Link to="/projects">Projects</Link>
              <Link to="/contact">Contact</Link>
            </Navigation>
        </Drawer>
        <Content>
            <div className="page-content" />
            <Main/>
        </Content>
    </Layout>
     </div>
    </HashRouter>
    );
  }
}

export default App;
